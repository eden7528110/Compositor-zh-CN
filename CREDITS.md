# 来源与致谢 / Credits & Attribution

本文件集中说明本仓库所含代码、模型与资源的来源。**本仓库仅为本地化派生作品，
不含任何原创功能实现。**

---

## 一、原始项目

### Compositor

* **作者**：Robbie Tilton / Wonder Assembly LLC
* **仓库**：https://github.com/robbietilton/Compositor
* **许可**：MIT，版权归 Wonder Assembly LLC
* **许可全文**：[`licenses/Compositor-MIT.txt`](licenses/Compositor-MIT.txt)
* **在本项目中的角色**：代码基线。本仓库的全部功能均源自此项目。

Compositor 是一款 macOS 平台的图层式图像合成器，采用 Swift / AppKit / Metal
实现。其命令体系（189 条命令、门控条件、准备阶段）、工具设计、图层模型与
快捷键方案，构成了本项目的全部基础。

原作者未对 Windows 移植版及本本地化版本做任何背书。

---

## 二、代码基线

### CompositorWindows

* **作者**：IAmTheBlurr 及社区贡献者
* **仓库**：https://github.com/IAmTheBlurr/CompositorWindows
* **许可**：MIT
* **版本**：v0.1.4-preview
* **上游基线**：Compositor `a19db9011282399785dc18efcfded904627bdcc2`（1.0.4）
* **在本项目中的角色**：本仓库代码的直接来源。

该移植版以 C++17 / Qt 6.8.3 / DirectX 11 重写了 Compositor 的全部功能，
使其可在 Windows 11 x64 上原生运行，并提供便携版打包。

本仓库基于该版本，仅替换界面显示文本为简体中文。

---

## 三、离线前景抠图模型

### BiRefNet / birefnet-lite

* **作者**：ZhengPeng7 及贡献者
* **仓库**：https://github.com/ZhengPeng7/BiRefNet
* **许可**：MIT
* **许可全文**：[`licenses/BiRefNet-MIT.txt`](licenses/BiRefNet-MIT.txt)
* **在本项目中的角色**：背景移除功能所使用的离线主体分割模型。

模型权重约 173 MB，因超出 GitHub 单文件 100 MB 限制，未纳入版本库，
请从 [Releases](../../releases) 获取。

模型卡：[`licenses/BiRefNet-lite-model-card.md`](licenses/BiRefNet-lite-model-card.md)

---

## 四、运行时依赖

以下组件在编译产物中动态链接，**不适用**本仓库的 MIT 许可，
各自适用其原始许可：

| 组件 | 版本 | 许可 | 许可全文 |
|---|---|---|---|
| Qt | 6.8.3 | LGPL-3.0（含组件级声明） | 发行包 `licenses/Qt/`、`licenses/Qt-SBOM/` |
| libheif | 1.23.4 | LGPL-3.0-or-later | 发行包 `licenses/libheif-COPYING.txt` |
| libde265 | 1.1.3 | LGPL-3.0-or-later | 发行包 `licenses/libde265-COPYING.txt` |
| ONNX Runtime | 1.30.0 | MIT | 发行包 `licenses/ONNX-Runtime-LICENSE.txt` |
| Microsoft VC++ 运行时 | — | Microsoft 条款 | 应用本地随附 |
| Windows 系统组件 | — | 随 Windows 11 提供 | — |

LGPL 组件允许用户替换应用目录下的 DLL 后直接运行本程序。
对应源码归档见发行包 `sources/` 目录。

混合许可的总体说明见：[`licenses/Inter-LICENSE.txt`](licenses/Inter-LICENSE.txt)

---

## 五、应用图标

原始几何应用图标由 Compositor 项目提供，适用该项目的 MIT 许可。
本项目未使用任何 Apple 商标图标。

---

## 六、本仓库的贡献

以下内容为本仓库维护者新增：

* `src/src/ui/UiText.h` / `UiText.cpp` —— 英中翻译表与翻译函数
* `src/src/ui/UiText.cpp` 中的 `addCommandMenu()` 菜单构造辅助函数
* `MainWindow::action()` 中显示文本与命令查找键分离的改造
* 各界面文件中将英文显示文本包裹为 `ui::zh(...)` 的改动
* `main.cpp` 中的 `installChinese()` 翻译加载函数
* `build-scripts/` 下的 Windows 构建脚本

以上内容同样以 MIT 许可发布。

---

## 七、致谢

**Robbie Tilton** —— 创作了 Compositor，本项目的一切基础。
**IAmTheBlurr** —— 完成了高质量的 Windows 移植，让这一切成为可能。
**ZhengPeng7** —— 贡献了离线前景抠图模型。
**Qt / libheif / libde265 / ONNX Runtime** 项目的所有贡献者。

发现问题时，请优先向上游对应项目反馈。