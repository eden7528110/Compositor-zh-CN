#!/usr/bin/env python3
"""Push Compositor-zh-CN to GitHub: create repo, push source, tag, release, upload ZIP.

Credentials are read from github-credentials.txt next to this script:
    USERNAME=<github login>
    TOKEN=<personal access token with 'repo' scope>
"""
import base64
import io
import json
import os
import subprocess
import sys
import time
import urllib.error
import urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))
CRED = os.path.join(HERE, 'github-credentials.txt')
REPO_NAME = 'Compositor-zh-CN'
TAG = 'v1.0.0-zh.1'
API = 'https://api.github.com'


def log(msg):
    print(msg, flush=True)


def load_credentials():
    if not os.path.exists(CRED):
        log('[x] Missing github-credentials.txt')
        log("    Create it from github-credentials.txt.example and fill in USERNAME / TOKEN.")
        sys.exit(1)
    cfg = {}
    with io.open(CRED, encoding='utf-8-sig') as fh:
        for line in fh:
            line = line.strip()
            if not line or line.startswith('#') or '=' not in line:
                continue
            k, v = line.split('=', 1)
            cfg[k.strip().upper()] = v.strip()
    user = cfg.get('USERNAME', '')
    token = cfg.get('TOKEN', '')
    if not user or not token:
        log('[x] USERNAME or TOKEN missing in github-credentials.txt')
        sys.exit(1)
    return user, token


def make_headers(token):
    return {
        'Authorization': 'Bearer ' + token,
        'Accept': 'application/vnd.github+json',
        'X-GitHub-Api-Version': '2022-11-28',
        'User-Agent': 'Compositor-zh-CN-publisher',
    }


def api(method, url, token, body=None, raw=None, content_type=None):
    headers = make_headers(token)
    data = None
    if body is not None:
        data = json.dumps(body).encode('utf-8')
        headers['Content-Type'] = 'application/json; charset=utf-8'
    elif raw is not None:
        data = raw
        headers['Content-Type'] = content_type
    req = urllib.request.Request(url, data=data, headers=headers, method=method)
    with urllib.request.urlopen(req, timeout=1800) as resp:
        payload = resp.read()
        return json.loads(payload) if payload else {}


def run_git(args, env=None):
    full = dict(os.environ)
    if env:
        full.update(env)
    proc = subprocess.run(['git'] + args, cwd=HERE, env=full,
                          capture_output=True, text=True, encoding='utf-8', errors='replace')
    if proc.returncode != 0:
        log('    git ' + ' '.join(args) + ' -> exit ' + str(proc.returncode))
        if proc.stdout.strip():
            log(proc.stdout.strip())
        if proc.stderr.strip():
            log(proc.stderr.strip())
        sys.exit(1)
    return proc.stdout.strip()


def main():
    user, token = load_credentials()

    log('[1/6] Verifying token ...')
    me = api('GET', API + '/user', token)
    login = me.get('login', '')
    if login.lower() != user.lower():
        log('[!] github-credentials.txt USERNAME=%s but token belongs to %s' % (user, login))
        log('    Using the token identity: %s' % login)
    name = me.get('name') or login
    email = me.get('email') or (login + '@users.noreply.github.com')
    log('    ok: %s <%s>' % (login, email))

    log('[2/6] Creating public repository %s/%s ...' % (login, REPO_NAME))
    repo_body = {
        'name': REPO_NAME,
        'description': 'Compositor 简体中文版 —— Windows 移植版的完整简体中文本地化（原作 Compositor by Wonder Assembly LLC / Robbie Tilton，MIT 许可）',
        'private': False,
        'auto_init': False,
        'has_issues': True,
        'has_wiki': False,
    }
    try:
        api('POST', API + '/user/repos', token, body=repo_body)
        log('    created')
    except urllib.error.HTTPError as e:
        if e.code == 422:
            log('    already exists, reuse it')
        else:
            log('[x] create repo failed: HTTP %s %s' % (e.code, e.read().decode('utf-8', 'replace')[:300]))
            sys.exit(1)

    log('[3/6] Setting git author identity ...')
    subprocess.run(['git', 'config', 'user.name', name], cwd=HERE, capture_output=True)
    subprocess.run(['git', 'config', 'user.email', email], cwd=HERE, capture_output=True)

    remote = 'https://github.com/%s/%s.git' % (login, REPO_NAME)
    run_git(['remote', 'remove', 'origin'])
    run_git(['remote', 'add', 'origin', remote])
    run_git(['branch', '-M', 'main'])

    log('[4/6] Pushing source to main ...')
    askpass = os.path.join(HERE, '.git-askpass.py')
    with io.open(askpass, 'w', encoding='utf-8', newline='\n') as fh:
        fh.write('#!/usr/bin/env python3\nimport sys\nsys.stdout.write(%r)\n' % token)
    os.chmod(askpass, 0o700)
    push_env = {
        'GIT_TERMINAL_PROMPT': '0',
        'GIT_ASKPASS': askpass,
        'GIT_USERNAME': login,
    }
    try:
        run_git(['push', '-u', 'origin', 'main'], env=push_env)
    finally:
        try:
            os.remove(askpass)
        except OSError:
            pass
    log('    source pushed')

    log('[5/6] Tagging %s and creating the release ...' % TAG)
    existing = subprocess.run(['git', 'tag', '-l', TAG], cwd=HERE,
                              capture_output=True, text=True).stdout.strip()
    if existing:
        run_git(['tag', '-d', TAG])
    run_git(['tag', '-a', TAG, '-m', 'Compositor 简体中文版 v1.0.0-zh.1'])
    run_git(['push', 'origin', TAG], env=push_env)

    body_path = os.path.join(HERE, '.release-body.md')
    notes = io.open(body_path, encoding='utf-8').read() if os.path.exists(body_path) else ''
    release = api('POST', API + '/repos/%s/%s/releases' % (login, REPO_NAME), token, body={
        'tag_name': TAG,
        'name': 'Compositor 简体中文版 v1.0.0-zh.1',
        'body': notes,
        'draft': False,
        'prerelease': False,
    })
    log('    release: ' + release.get('html_url', ''))

    log('[6/6] Uploading the portable ZIP as a release asset ...')
    desktop = os.path.join(os.path.expanduser('~'), 'Desktop')
    candidates = [f for f in os.listdir(desktop) if f.lower().endswith('.zip')
                  and 'Compositor' in f]
    if not candidates:
        log('[!] No Compositor ZIP found on the Desktop; upload it manually.')
    else:
        candidates.sort(key=lambda f: os.path.getmtime(os.path.join(desktop, f)), reverse=True)
        fname = candidates[0]
        fpath = os.path.join(desktop, fname)
        size = os.path.getsize(fpath)
        log('    %s (%.1f MB) - this can take a few minutes ...' % (fname, size / 1048576.0))
        upload_url = ('https://uploads.github.com/repos/%s/%s/releases/%s/assets?name=%s'
                      % (login, REPO_NAME, release['id'],
                         urllib.parse.quote(fname.encode('utf-8'))))
        with open(fpath, 'rb') as fh:
            asset = api('POST', upload_url, token, raw=fh, content_type='application/zip')
        log('    asset: ' + asset.get('browser_download_url', ''))

    log('')
    log('=== done ===')
    log('repository: https://github.com/%s/%s' % (login, REPO_NAME))
    log('release:    https://github.com/%s/%s/releases/tag/%s' % (login, REPO_NAME, TAG))


if __name__ == '__main__':
    import urllib.parse
    main()