# Compositor 简体中文版

Windows 11 x64 图像合成器 **Compositor** 的完整简体中文本地化版本。

界面所有菜单、工具栏、面板、右键菜单、对话框、按钮、状态栏与错误提示均已汉化，
软件名称 `Compositor` 保持不变。

---

## 致原作者与致上游社区

本仓库**不是**原始项目。它是一个派生作品，包含大量他人成果，在此逐一说明来源：

| 角色 | 项目 | 作者 | 许可 |
|---|---|---|---|
| **原始项目** | [Compositor](https://github.com/robbietilton/Compositor) | **Robbie Tilton** / Wonder Assembly LLC | MIT |
| **Windows 移植版（本仓库基线）** | [CompositorWindows](https://github.com/IAmTheBlurr/CompositorWindows) | IAmTheBlurr 及社区贡献者 | MIT |
| **离线前景抠图模型** | [BiRefNet](https://github.com/ZhengPeng7/BiRefNet) | ZhengPeng7 及贡献者 | MIT |

**特别致谢原作者 Robbie Tilton。** 原始 Compositor 是一款设计精良的 macOS 图像合成器，
其交互设计、命令体系与快捷键方案构成了本项目的全部基础。本仓库所做的仅为界面文字的
本地化工作，未改动任何功能逻辑，也未对原作的设计决策做任何评价或重构。

**特别致谢 IAmTheBlurr。** 其独立完成的 Windows 移植版（C++ / Qt 6 / DirectX 11）
是本仓库的代码基线。正是这一高质量移植让 Windows 用户得以使用 Compositor，
本仓库的汉化才得以建立在可编译的源代码之上。

上游原作者**未对**本仓库背书。本项目与 macOS 原版的功能一致性、以及与 Adobe Photoshop
的完整兼容性，均不作任何声称。若发现缺陷，请优先向上游对应项目反馈。

---

## 本仓库做了什么

仅一项：**把界面文本从英文改为简体中文**，并为此调整了构建流程。

具体包括：

* 新增 `src/src/ui/UiText.h` / `UiText.cpp` ——集中式翻译表，约 300 条英中对照
* 新增 `ui::zh()` 显示翻译函数与 `ui::addCommandMenu()` 菜单构造辅助函数
* 调整 `MainWindow::action()`，使**显示文本**与**命令查找键**分离
* 新增 `build-scripts/`，记录完整的 Windows 构建流程（含本机构建环境的绕过方案）

**未改动**：任何图像处理算法、渲染管线、命令 ID、快捷键、启用状态判定、项目文件格式。

### 一个值得说明的设计约束

上游代码中，菜单项的文本**同时**承担两个职责——既是显示文本，又是命令查找键：

```cpp
// 上游原始写法
auto* item = menu->addAction(name);          // 显示
bindCommand(item, menu->title(), name, ...); // 查找键
```

直接替换成中文会导致 `commandSpec()` 匹配失败，所有菜单项变灰不可用。

本仓库的解法是**把两者彻底分离**：

```cpp
// 本仓库写法
auto* item = menu->addAction(ui::zh(name));              // 显示中文
const QString menuKey = menu->property("commandMenu").toString();
bindCommand(item, menuKey, name, std::move(invoke));     // 仍传英文键
```

菜单标题的英文原文保存在 QMenu 的 `commandMenu` 属性中。因此
**`CommandRegistry.cpp` 的 189 条命令目录一行未改**，全部快捷键
（`Ctrl+N` / `Ctrl+Z` / `Ctrl+Shift+E` / `Ctrl+]` …）与命令启用状态
与英文版完全一致。

---

## 下载

编译好的便携版（Windows 11 x64，237 MB）发布在
**[Releases](../../releases)** 页面，解压即可运行，无需安装。

> GitHub 单文件上限 100 MB，离线抠图模型（173 MB）与 Qt 源码包（47 MB）
> 未纳入版本库，请从 Release 附件获取完整可运行包。

**运行环境**：Windows 11 x64。包内已含离线模型与全部运行库，无需联网。

---

## 从源码构建

依赖：Visual Studio Build Tools（MSVC x64）、Windows 11 SDK、CMake、Ninja、
Python 3、Qt 6.8.3、libheif、libde265、ONNX Runtime。

```powershell
# 1. 准备 MSVC 环境（本机 VS 路径非标准，脚本已绕过 vswhere）
.\build-scripts\msvc_env.ps1

# 2. 下载并编译 Qt 6.8.3
.\build-scripts\qt_setup.ps1

# 3. 准备成像依赖（libheif / libde265 / ONNX Runtime / 模型）
.\build-scripts\imaging_setup.ps1

# 4. 编译
.\build-scripts\build_one.ps1
```

### 构建环境中的几个坑（已在脚本中处理）

* **Visual Studio 18 路径非标准**，`vswhere` 枚举不到实例，故项目自带的
  `bootstrap.ps1` / `vcvarsall.bat` 全部失效。`msvc_env.ps1` 改为手动设置
  `PATH` / `INCLUDE` / `LIB`。
* **MSVC 并行编译会静默崩溃**（8 路时 `cl.exe` 无输出直接退出，错误码 1）。
  脚本固定使用 `-j 2`。
* **`lock.json` 的 DLL 哈希校验必然失败**：本机 MSVC 14.51 与维护者 14.44
  产物不同。`imaging_setup.ps1` 会用本机构建的实际哈希更新该文件。
* **PowerShell 的 `Path` / `PATH` 键冲突**会导致 `Start-Process` 与
  `vcvarsall` 报错，脚本已规避。

---

## 汉化覆盖率

已汉化：

* 12 个顶级菜单（文件 / 编辑 / 图层 / 图像 / 视图 / 帮助 / 调整 / 滤镜 /
  选择 / 剪贴板 / 变换 / 画布）
* 工具栏、左侧工具按钮、右侧图层面板与变换面板
* 图层右键菜单及其蒙版子菜单
* 新建画布卡片、导入导出对话框、调整与滤镜面板、背景移除对话框
* 全部状态栏消息、进度提示与错误对话框

未汉化（有意保留）：

* 软件名称 `Compositor`（窗口标题、任务栏、关于对话框）
* 上游项目链接与技术标识符

---

## 许可

本仓库采用 MIT 协议，完整文本见 [`LICENSE`](LICENSE)。

原项目的 MIT 许可要求保留原始版权声明，已在该文件中完整保留
（`Copyright (c) 2026 Wonder Assembly LLC`）。

Qt、libheif、libde265 等 LGPL 组件、以及 ONNX Runtime 与 MSVC 运行库的
各自许可文本，见 [`licenses/`](licenses/) 目录与发行包内的 `licenses/` 目录。

LGPL 组件允许用户替换应用目录下的 DLL 后直接运行本程序。

---

## 免责声明

本项目为社区作品，**未获原作者认可**，与 macOS 原版的功能一致性未经完整验证。
本仓库按「现状」提供，不承担任何担保责任。请保持 Windows 安全防护开启，
并从本项目发布的链接获取程序。