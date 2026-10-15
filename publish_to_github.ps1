#requires -Version 5.1
<#
  一键发布 Compositor-zh-CN 到 GitHub
  用法：在 PowerShell 中执行
      powershell -ExecutionPolicy Bypass -File .\publish_to_github.ps1
  然后按提示输入：GitHub 用户名 + Personal Access Token（repo 权限）
#>

$ErrorActionPreference = 'Stop'
$repoDir   = $PSScriptRoot
$repoName  = 'Compositor-zh-CN'
$tagName   = 'v1.0.0-zh.1'
$zipPath = (Get-ChildItem -LiteralPath (Join-Path $env:USERPROFILE 'Desktop') -Filter '*.zip' -ErrorAction SilentlyContinue |
    Sort-Object LastWriteTime -Descending | Select-Object -First 1)
$zipPath = if ($zipPath) { $zipPath.FullName } else { $null }

Write-Host ''
Write-Host '=== Compositor-zh-CN -> GitHub 发布向导 ===' -ForegroundColor Cyan
Write-Host ''

# ---------- 1. 收集账号信息 ----------
$UserName = Read-Host 'GitHub 用户名'
if ([string]::IsNullOrWhiteSpace($UserName)) { throw '用户名不能为空' }

$SecurePat = Read-Host 'Personal Access Token (repo 权限，输入不回显)' -AsSecureString
$Pat = [System.Runtime.InteropServices.Marshal]::PtrToStringAuto(
    [System.Runtime.InteropServices.Marshal]::SecureStringToBSTR($SecurePat))

$headers = @{
    'Authorization' = "Bearer $Pat"
    'Accept'        = 'application/vnd.github+json'
    'X-GitHub-Api-Version' = '2022-11-28'
    'User-Agent'    = 'Compositor-zh-CN-publisher'
}

# ---------- 2. 校验 Token ----------
Write-Host "`n[1/5] 校验 Token ..." -ForegroundColor Yellow
try {
    $me = Invoke-RestMethod -Uri 'https://api.github.com/user' -Headers $headers -Method Get
} catch {
    throw "Token 校验失败：$($_.Exception.Message)"
}
Write-Host "      登录身份：$($me.login) <$($me.email)>" -ForegroundColor Green

# ---------- 3. 设置 commit 作者 ----------
Push-Location $repoDir
try {
    git config user.name  $me.login
    if ($me.email) { git config user.email $me.email }
    else { git config user.email "$($me.login)@users.noreply.github.com" }
    Write-Host '      已设置 git 作者身份' -ForegroundColor Green

    # ---------- 4. 创建仓库 ----------
    Write-Host "`n[2/5] 创建仓库 $UserName/$repoName ..." -ForegroundColor Yellow
    $body = @{
        name        = $repoName
        description = 'Compositor Windows 移植版 · 简体中文本地化（基于 Wonder Assembly LLC / robbietilton 的 Compositor，MIT 许可）'
        private     = $false
        auto_init   = $false
    } | ConvertTo-Json
    try {
        $null = Invoke-RestMethod -Uri 'https://api.github.com/user/repos' -Headers $headers -Method Post -Body ([Text.Encoding]::UTF8.GetBytes($body)) -ContentType 'application/json; charset=utf-8'
        Write-Host '      仓库已创建' -ForegroundColor Green
    } catch {
        if ($_.Exception.Response.StatusCode.value__ -eq 422) {
            Write-Host '      仓库已存在，跳过创建' -ForegroundColor DarkGray
        } else { throw }
    }

    git remote remove origin 2>$null
    git remote add origin "https://github.com/$UserName/$repoName.git"
    git branch -M main
    Write-Host "`n[3/5] 推送源码到 main ..." -ForegroundColor Yellow
    git push -u origin main
    if ($LASTEXITCODE -ne 0) { throw 'git push 失败' }
    Write-Host '      推送完成' -ForegroundColor Green

    # ---------- 5. 打 tag 并创建 Release ----------
    Write-Host "`n[4/5] 创建 Release $tagName ..." -ForegroundColor Yellow
    git tag -a $tagName -m 'v1.0.0-zh.1 简体中文本地化发布'
    git push origin $tagName

    $relBodyPath = Join-Path $repoDir '.release-body.md'
    $relBody = Get-Content -LiteralPath $relBodyPath -Raw -Encoding UTF8
    $relJson = @{
        tag_name         = $tagName
        name             = 'v1.0.0-zh.1 · 简体中文本地化版'
        body             = $relBody
        draft            = $false
        prerelease       = $false
    } | ConvertTo-Json
    $rel = Invoke-RestMethod -Uri "https://api.github.com/repos/$UserName/$repoName/releases" -Headers $headers -Method Post -Body ([Text.Encoding]::UTF8.GetBytes($relJson)) -ContentType 'application/json; charset=utf-8'
    Write-Host "      Release 已创建：$($rel.html_url)" -ForegroundColor Green

    # ---------- 6. 上传 ZIP ----------
    if (Test-Path -LiteralPath $zipPath) {
        Write-Host "`n[5/5] 上传便携版 ZIP（237MB，请耐心等待）..." -ForegroundColor Yellow
        $assetUrl = "https://uploads.github.com/repos/$UserName/$repoName/releases/$($rel.id)/assets?name=$([uri]::EscapeDataString((Split-Path $zipPath -Leaf)))"
        $asset = Invoke-RestMethod -Uri $assetUrl -Headers $headers -Method Post `
            -ContentType 'application/zip' -InFile $zipPath
        Write-Host "      附件已上传：$($asset.browser_download_url)" -ForegroundColor Green
    } else {
        Write-Host "`n[5/5] 未找到桌面 ZIP（$zipPath），已跳过附件上传。" -ForegroundColor Yellow
        Write-Host "      请手动到 Release 页面上传该 ZIP。" -ForegroundColor Yellow
    }

    Write-Host ''
    Write-Host '=== 全部完成 ===' -ForegroundColor Green
    Write-Host "仓库：https://github.com/$UserName/$repoName"
    Write-Host "Release：$($rel.html_url)"
}
finally {
    Pop-Location
    $Pat = $null
}