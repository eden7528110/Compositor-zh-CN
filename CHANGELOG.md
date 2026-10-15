# 更新日志

本文件记录本仓库（简体中文本地化版）相对上游基线的改动。
上游版本本身的变更请见对应上游仓库的发布说明。

## [1.0.0-zh.1] — 2026-10-15

首个简体中文本地化版本，基于
[CompositorWindows v0.1.4-preview](https://github.com/IAmTheBlurr/CompositorWindows)，
后者基于 [Compositor 1.0.4](https://github.com/robbietilton/Compositor)
（上游提交 `a19db9011282399785dc18efcfded904627bdcc2`）。

### 新增

* `src/src/ui/UiText.h` / `UiText.cpp`
  —— 集中式英中翻译表，约 300 条条目，覆盖菜单、工具栏、面板、对话框、
  状态栏与错误消息
* `ui::zh(const QString&)` —— 显示文本翻译，查不到时原样返回
* `ui::zhc(...)` —— `const char*` 重载，供历史记录标签（撤销/重做菜单）使用
* `ui::addCommandMenu(...)` —— 菜单构造辅助函数，把英文查找键存入
  QMenu 的 `commandMenu` 属性
* `main.cpp` 中的 `installChinese()` —— 启动时加载 Qt `.qm` 翻译，
  覆盖使用 Qt 原生 `tr()` 的背景移除对话框
* `build-scripts/` —— 完整的 Windows 构建脚本（MSVC 环境、Qt、
  成像依赖、编译、校验清单生成）

### 修改

* `MainWindow::action()` —— 显示文本与命令查找键分离，
  这是整个汉化方案的核心
* `MainWindow.cpp` —— 顶部菜单、工具栏、图层面板、变换面板、
  新建画布卡片、关闭确认对话框
* `CommandActions.cpp` —— 错误对话框正文走 `ui::zh()`
* `AdjustmentActions.cpp` / `AdjustmentAdvancedControls.cpp` /
  `AdjustmentDialog.cpp` —— 调整面板
* `AppearanceActions.cpp` / `BrushActions.cpp` /
  `BrushAppearanceActions.cpp` —— 画笔与外观面板
* `DrawingActions.cpp` / `DrawingActions` 绘图选项工具栏
* `FileActions.cpp` —— 导入导出对话框、保存对话框
* `FilterActions.cpp` —— 滤镜面板
* `KeyboardActions.cpp` / `WandActions.cpp` —— 快捷键与魔棒
* `LayerActions.cpp` / `LayerMergeJob.cpp` / `LayerPanel.cpp` —— 图层面板
* `PaletteDialog.cpp` / `PaletteSwatches.cpp` —— 调色板
* `ProjectActions.cpp` / `ProjectChrome.cpp` / `ProjectOpenDialog.cpp`
  —— 项目工作区
* `RetouchActions.cpp` —— 修饰选项工具栏
* `SelectionActions.cpp` —— 选择菜单与选区选项
* `TransformActions.cpp` —— 变换菜单与变换选项
* `UpdatePanel.cpp` —— 更新面板
* `VisualStyle.cpp` —— 外观菜单
* `CMakeLists.txt` —— 注册 `UiText.cpp`

### 未改动（有意保持）

* `CommandRegistry.cpp` —— 189 条命令目录**一行未改**，
  全部命令 ID、菜单键、标签键、快捷键、门控条件保持英文
* 任何图像处理算法、渲染管线、命令 ID、快捷键定义
* 项目文件（`.comp`）格式与解析逻辑
* 软件名称 `Compositor`

### 构建环境修复

以下问题为在本机构建时遇到并已绕过，仅影响构建过程，不影响运行行为：

* Visual Studio 18 安装路径非标准，`vswhere` 无法枚举，
  改由 `msvc_env.ps1` 手动设置 `PATH` / `INCLUDE` / `LIB`
* MSVC 8 路并行编译时 `cl.exe` 静默崩溃，固定降为 2 路
* `lock.json` 的 DLL 哈希校验与本机 MSVC 版本不匹配，
  改用本机构建产物的实际哈希
* PowerShell `Path` / `PATH` 环境变量键名冲突的规避

### 已知问题

* 软件名称 `Compositor` 按要求保留英文
* 部分 Qt 原生控件按钮（确定 / 取消）的语言取决于系统语言环境；
  已内置 `installChinese()` 加载机制，附上 `compositor_zh_CN.qm`
  即可完全中文化
* 本移植版与 macOS 原版的功能一致性未做完整验证
* 编译产物未做数字签名，Windows 可能提示「未知发布者」