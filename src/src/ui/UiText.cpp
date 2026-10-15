// Simplified Chinese display strings for the Compositor Windows preview.
// Command lookup keys in CommandRegistry.cpp stay English on purpose: this
// table only affects text the user reads.
#include "UiText.h"
#include <QHash>
#include <QMenu>
#include <QMenuBar>
#include <string>

namespace compositor::ui {
namespace {

// Entries that carry a mnemonic ("&File") already spell the translated marker
// out in full ("文件(&F)"), so this only covers stripped spellings that are
// looked up without their '&'.
QString applyMnemonic(const QString& key, const QString& translated) {
    Q_UNUSED(key);
    if (translated.isEmpty() || translated.contains('&')) return translated;
    QString out = translated;
    out.insert(0, QLatin1Char('&'));
    return out;
}

const QHash<QString, QString>& table() {
    static const QHash<QString, QString> map = {
        // ---- Application / window -------------------------------------
        {"Compositor", "Compositor"},
        {"Compositor Windows", "Compositor Windows"},
        {"Create a canvas or import an image", "新建画布或导入图像"},

        // ---- Menus ------------------------------------------------------
        {"&File", "文件(&F)"},
        {"&Edit", "编辑(&E)"},
        {"&Layer", "图层(&L)"},
        {"&Image", "图像(&I)"},
        {"&Canvas", "画布(&C)"},
        {"&View", "视图(&V)"},
        {"&Help", "帮助(&H)"},
        {"&Select", "选择(&S)"},
        {"&Clipboard", "剪贴板(&C)"},
        {"&Transform", "变换(&T)"},
        {"&Adjustments", "调整(&A)"},
        {"&Filters", "滤镜(&F)"},
        {"New Adjustment Layer", "新建调整图层"},
        {"Mask", "蒙版"},
        {"Appearance", "外观"},

        // ---- File menu items --------------------------------------------
        {"&New Canvas\u2026", "新建画布(&N)\u2026"},
        {"&Import Image\u2026", "导入图像(&I)\u2026"},
        {"&Export Image\u2026", "导出图像(&E)\u2026"},
        {"Close Project", "关闭项目"},
        {"Exit", "退出"},
        {"&Open Project\u2026", "打开项目(&O)\u2026"},
        {"&Save Project", "保存项目(&S)"},
        {"Save Project &As\u2026", "项目另存为(&A)\u2026"},

        // ---- Edit menu items --------------------------------------------
        {"Undo", "撤销"},
        {"Redo", "重做"},

        // ---- Layer menu items -------------------------------------------
        {"New Layer", "新建图层"},
        {"Duplicate Layer", "复制图层"},
        {"Rename Layer\u2026", "重命名图层(&R)\u2026"},
        {"Delete Layer", "删除图层"},
        {"Raise Layer", "上移图层"},
        {"Lower Layer", "下移图层"},
        {"New Group", "新建组"},
        {"Group Selected", "编组所选图层"},
        {"Move Out of Group", "移出组"},
        {"Create / Release Clipping Mask", "创建/释放剪贴蒙版"},
        {"Merge Layers", "合并图层"},
        {"Copy Layer to Project\u2026", "复制图层到项目(&C)\u2026"},

        // ---- Mask menu items --------------------------------------------
        {"Add White Mask (Hide Selection)", "添加白蒙版（隐藏选区）"},
        {"Add Black Mask (Reveal Selection)", "添加黑蒙版（显示选区）"},
        {"Reveal All", "全部显示"},
        {"Hide All", "全部隐藏"},
        {"Enable / Disable Mask", "启用/停用蒙版"},
        {"Link / Unlink Mask", "链接/取消链接蒙版"},
        {"Delete Mask", "删除蒙版"},
        {"Edit Image", "编辑图像"},
        {"Edit Mask", "编辑蒙版"},
        {"Select Image Alpha", "选择图像透明区"},
        {"Select Mask Black Areas", "选择蒙版黑色区域"},

        // ---- Image / Canvas menu items ----------------------------------
        {"Fill\u2026", "填充(&F)\u2026"},
        {"Invert", "反相"},
        {"Canvas Size\u2026", "画布大小(&C)\u2026"},
        {"Image Size\u2026", "图像大小(&I)\u2026"},
        {"Flip Canvas Horizontally", "水平翻转画布"},
        {"Flip Canvas Vertically", "垂直翻转画布"},
        {"Crop Tool", "裁剪工具"},
        {"Apply Crop", "应用裁剪"},
        {"Cancel Crop", "取消裁剪"},

        // ---- View menu items --------------------------------------------
        {"Fit Canvas", "适合窗口"},
        {"Actual Pixels", "实际像素"},
        {"Pixel Grid", "像素网格"},

        // ---- Help menu items --------------------------------------------
        {"Check for Updates\u2026", "检查更新(&C)\u2026"},
        {"About Compositor", "关于 Compositor"},

        // ---- Clipboard menu items ---------------------------------------
        {"Cut", "剪切"},
        {"Copy", "复制"},
        {"Paste", "粘贴"},
        {"Copy Merged", "合并复制"},
        {"Layer via Copy", "通过复制创建图层"},
        {"Clear", "清除"},

        // ---- Select menu items ------------------------------------------
        {"All", "全选"},
        {"Deselect", "取消选择"},
        {"Inverse", "反选"},
        {"Expand\u2026", "扩展(&E)\u2026"},
        {"Contract\u2026", "收缩(&C)\u2026"},

        // ---- Transform menu items ---------------------------------------
        {"Free Transform", "自由变换"},
        {"Distort", "变形"},
        {"Apply Transform", "应用变换"},
        {"Cancel Transform", "取消变换"},
        {"Flip Layer Horizontally", "水平翻转图层"},
        {"Flip Layer Vertically", "垂直翻转图层"},
        {"Scale\u2026", "缩放(&S)\u2026"},
        {"Flip H", "水平翻转"},
        {"Flip V", "垂直翻转"},

        // ---- Adjustments / Filters ---------------------------------------
        {"Hue/Saturation\u2026", "色相/饱和度(&H)\u2026"},
        {"Levels\u2026", "色阶(&L)\u2026"},
        {"Curves\u2026", "曲线(&C)\u2026"},
        {"Exposure\u2026", "曝光度(&E)\u2026"},
        {"Gradient Map\u2026", "渐变映射(&G)\u2026"},
        {"Grain\u2026", "颗粒(&G)\u2026"},
        {"Edit Adjustment Layer\u2026", "编辑调整图层(&E)\u2026"},
        {"Gaussian Blur\u2026", "高斯模糊(&G)\u2026"},
        {"Motion Blur\u2026", "动态模糊(&M)\u2026"},
        {"Add Noise\u2026", "添加杂色(&N)\u2026"},
        {"Lens Correction\u2026", "镜头校正(&L)\u2026"},
        {"Content-Aware Fill\u2026", "内容识别填充(&C)\u2026"},
        {"Remove Background\u2026", "移除背景(&R)\u2026"},

        // ---- Toolbars / docks --------------------------------------------
        {"Tools", "工具"},
        {"Brush Options", "画笔选项"},
        {"Drawing Options", "绘图选项"},
        {"Selection Options", "选区选项"},
        {"Magic Wand Options", "魔棒选项"},
        {"Transform Options", "变换选项"},
        {"Retouch Options", "修饰选项"},
        {"Layers", "图层"},
        {"Transform", "变换"},
        {"Mac-style title bar", "mac 风格标题栏"},

        // ---- Tools --------------------------------------------------------
        {"Move (V)", "移动 (V)"},
        {"Hand (H)", "抓手 (H)"},
        {"Marquee (M)", "矩形选框 (M)"},
        {"Lasso (L)", "套索 (L)"},
        {"Polygon", "多边形"},
        {"Polygonal Lasso", "多边形套索"},
        {"Wand (W)", "魔棒 (W)"},
        {"Brush (B)", "画笔 (B)"},
        {"Eraser (E)", "橡皮擦 (E)"},
        {"Clone (S)", "仿制图章 (S)"},
        {"Clone Stamp", "仿制图章"},
        {"Clone Stamp (S)", "仿制图章 (S)"},
        {"Heal (J)", "修复画笔 (J)"},
        {"Spot Healing", "污点修复"},
        {"Spot Healing (J)", "污点修复 (J)"},
        {"Retouch (R)", "修饰 (R)"},
        {"Gradient (G)", "渐变 (G)"},
        {"Shape (U)", "形状 (U)"},
        {"Crop (C)", "裁剪 (C)"},
        {"Eyedropper (I)", "吸管 (I)"},
        {"Zoom (Z)", "缩放 (Z)"},
        {"Foreground", "前景色"},
        {"Background", "背景色"},
        {"Swap (X)", "交换 (X)"},
        {"Default (D)", "默认 (D)"},
        {"Foreground Color", "前景色"},
        {"Background Color", "背景色"},

        // ---- Drawing / gradient / shape -----------------------------------
        {"Apply Gradient", "应用渐变"},
        {"Cancel Gradient", "取消渐变"},
        {"Update Shape Style", "更新形状样式"},
        {"Rectangle", "矩形"},
        {"Ellipse", "椭圆"},
        {"Anchor", "锚点"},
        {"Top left", "左上"},
        {"Top right", "右上"},
        {"Bottom left", "左下"},
        {"Bottom right", "右下"},
        {"Foreground to Background", "前景色到背景色"},
        {"Foreground to Transparent", "前景色到透明"},
        {"Choose Color\u2026", "选择颜色(&C)\u2026"},
        {"Canvas extension color", "画布扩展颜色"},
        {"Resampling", "重采样"},
        {"Units", "单位"},
        {"Resolution (pixels/inch)", "分辨率（像素/英寸）"},
        {"High quality", "高质量"},
        {"Lock aspect ratio", "锁定宽高比"},
        {"Gradient opacity", "渐变不透明度"},
        {"Corner radius", "圆角半径"},
        {"Crop ratio", "裁剪比例"},
        {" px radius", " 像素半径"},

        // ---- Brush / retouch controls -------------------------------------
        {"Editing target", "编辑目标"},
        {"Brush diameter", "画笔直径"},
        {"Brush hardness", "画笔硬度"},
        {"Brush opacity", "画笔不透明度"},
        {"Brush hardness slider", "画笔硬度滑块"},
        {"Brush opacity slider", "画笔不透明度滑块"},
        {"Opacity percent", "不透明度百分比"},
        {"Healing mode", "修复模式"},
        {"Smear mode", "涂抹模式"},
        {"Retouch diameter", "修饰直径"},
        {"Retouch hardness", "修饰硬度"},
        {"Retouch opacity", "修饰不透明度"},
        {"Retouch hardness slider", "修饰硬度滑块"},
        {"Retouch opacity slider", "修饰不透明度滑块"},
        {"Sample All Layers", "采样所有图层"},
        {"Show controls", "显示控件"},
        {"Auto-select layer", "自动选择图层"},
        {"Snap to edges and centers", "吸附边缘与中心"},
        {"Paint mask white", "将蒙版涂白"},

        // ---- Selection controls --------------------------------------------
        {"Marquee shape", "选框形状"},
        {"Lasso kind", "套索类型"},
        {"Selection mode", "选择模式"},
        {"Wand tolerance", "魔棒容差"},
        {"Wand sample size", "魔棒取样大小"},
        {"New selection", "新建选区"},
        {"Point Sample", "点采样"},
        {"Tolerance ", "容差 "},
        {" px", " 像素"},

        // ---- Transform controls ---------------------------------------------
        {"Transform scale percent", "变换缩放百分比"},
        {"Transform sampling", "变换采样"},

        // ---- Layer panel ------------------------------------------------------
        {"Layer blend mode", "图层混合模式"},
        {"Layer opacity", "图层不透明度"},
        {"Layer list", "图层列表"},
        {"Layer editing target", "图层编辑目标"},
        {"Add Mask", "添加蒙版"},
        {"Delete", "删除"},
        {"Group", "编组"},
        {"Bake Appearance", "固化外观"},
        {"Remove Clipping Links", "移除剪贴链接"},
        {"Destination project", "目标项目"},
        {"New Project", "新建项目"},
        {"Hide / Show Layer", "隐藏/显示图层"},
        {"Enable Mask", "启用蒙版"},
        {"Disable Mask", "停用蒙版"},
        {"Link Mask", "链接蒙版"},
        {"Unlink Mask", "取消链接蒙版"},
        {"Release Clipping Mask", "释放剪贴蒙版"},
        {"Delete Selected Layers", "删除所选图层"},
        {"Duplicate Layers", "复制图层"},
        {"Move Layers", "移动图层"},
        {"Transform Layers", "变换图层"},
        {"Distort Layers", "变形图层"},
        {"Transform Layer", "变换图层"},
        {"Transform Layer Mask", "变换图层蒙版"},
        {"Distort Layer Mask", "变形图层蒙版"},
        {"Transform Selection", "变换选区"},
        {"Link mask", "链接蒙版"},
        {"Unlink mask", "取消链接蒙版"},
        {"Link mask: ", "链接蒙版："},
        {"Unlink mask: ", "取消链接蒙版："},
        {"Select image: ", "选择图像："},
        {"Select mask: ", "选择蒙版："},
        {"Clipped to ", "剪贴于 "},
        {"Select image; Ctrl-click selects alpha, Ctrl+Shift adds, Ctrl+Alt subtracts",
         "选择图像；Ctrl 单击选择透明区，Ctrl+Shift 加选，Ctrl+Alt 减选"},
        {"Select mask; Shift-click enables/disables; Ctrl-click selects black areas; Alt-drag copies mask",
         "选择蒙版；Shift 单击启用/停用，Ctrl 单击选择黑色区域，Alt 拖动复制蒙版"},

        // ---- Palette ----------------------------------------------------------
        {"Foreground and background colors", "前景色与背景色"},
        {"New and original colors", "新颜色与原颜色"},
        {"Hex color", "十六进制颜色"},
        {"Saturation and brightness", "饱和度与明度"},
        {"Click the canvas to sample", "点击画布取样"},
        {"Foreground color", "前景色"},
        {"Background color", "背景色"},
        {"Default colors", "默认颜色"},
        {"Swap colors", "交换颜色"},
        {"Default colors (D)", "默认颜色 (D)"},
        {"Swap foreground and background (X)", "交换前景色与背景色 (X)"},
        {"Up and Down change hue by one degree. Hold Shift for ten degrees.",
         "上下方向键按一度调整色相，按住 Shift 调整十度。"},
        {"Left and Right change saturation. Up and Down change brightness. Hold Shift for ten percent.",
         "左右方向键调整饱和度，上下方向键调整明度，按住 Shift 调整百分之十。"},
        {"Mask foreground", "遮罩前景色"},
        {"Mask background", "遮罩背景色"},
        {"Color Picker (Foreground Color)", "颜色选择器（前景色）"},
        {"Color Picker (Background Color)", "颜色选择器（背景色）"},

        // ---- Project workspace -------------------------------------------------
        {"New Canvas", "新建画布"},
        {"New canvas", "新建画布"},
        {"Create canvas", "创建画布"},
        {"Import image", "导入图像"},
        {"Open project", "打开项目"},
        {"Width (pixels)", "宽度（像素）"},
        {"Height (pixels)", "高度（像素）"},
        {"Width in pixels", "宽度（像素）"},
        {"Height in pixels", "高度（像素）"},
        {"Transparent canvas \u00b7 sRGB", "透明画布 · sRGB"},
        {"New canvas \u00b7 Drop images or layers here for new projects",
         "新建画布 · 将图像或图层拖放到此处以创建新项目"},
        {"New canvas; drop into a new project", "新建画布；拖放以创建新项目"},
        {"Project workspace", "项目工作区"},
        {"Project tabs", "项目标签页"},
        {"Open Compositor Project", "打开 Compositor 项目"},
        {"Open Compositor Projects", "打开 Compositor 项目"},
        {"Save Compositor Project", "保存 Compositor 项目"},
        {"Compositor project directory (*.comp)", "Compositor 项目目录 (*.comp)"},
        {"Choose a folder outside a .comp project.", "请选择 .comp 项目之外的文件夹。"},
        {"Select a .comp project. Double-click folders to browse.",
         "请选择 .comp 项目。双击文件夹可浏览。"},
        {"Parent folder", "上级文件夹"},
        {"Project folders", "项目文件夹"},
        {"Folder path", "文件夹路径"},
        {"Open project ", "打开项目"},
        {"Copy Layer to Project", "复制图层到项目"},
        {"Copy Layers from Project", "从项目复制图层"},
        {"Unsaved Changes", "未保存的更改"},
        {"Save changes before closing this project?", "关闭此项目前要保存更改吗？"},

        // ---- Import / export ----------------------------------------------------
        {"Import Images", "导入图像"},
        {"Importing images\u2026", "正在导入图像\u2026"},
        {"Receiving dropped images\u2026", "正在接收拖入的图像\u2026"},
        {"Waiting for the image provider to finish cancelling\u2026",
         "正在等待图像提供程序完成取消\u2026"},
        {"Export Image", "导出图像"},
        {"Updating preview\u2026", "正在更新预览\u2026"},
        {"Cannot display export preview", "无法显示导出预览"},
        {"Saving image\u2026", "正在保存图像\u2026"},
        {"Image import cancelled", "已取消图像导入"},
        {"Some images could not be imported.", "部分图像无法导入。"},
        {"Some dropped items could not be read.", "部分拖入的内容无法读取。"},
        {"The import destination was closed.", "导入目标已关闭。"},
        {"The drop destination was closed", "拖放目标已关闭"},
        {"Cannot open image", "无法打开图像"},
        {"Image decoder is required", "需要图像解码器"},
        {"Invalid image drop point", "无效的图像拖放位置"},
        {"Incomplete import host", "导入宿主不完整"},
        {"This project exceeds the 100-megapixel import budget",
         "此项目超过 1 亿像素的导入上限"},
        {"Cannot copy dropped image data", "无法复制拖入的图像数据"},
        {"Cannot create dropped-image temporary storage", "无法创建拖入图像的临时存储"},
        {"Cannot create image export storage", "无法创建图像导出存储"},
        {"Images (*.png *.jpg *.jpeg *.tif *.tiff *.heic *.heif);;All files (*)",
         "图像 (*.png *.jpg *.jpeg *.tif *.tiff *.heic *.heif);;所有文件 (*)"},
        {"Choose PNG, JPEG, TIFF or bundled HEIC", "选择 PNG、JPEG、TIFF 或内置 HEIC 格式"},
        {"Cannot read HEIC file", "无法读取 HEIC 文件"},
        {"Bundled HEVC decoder is unavailable", "内置 HEVC 解码器不可用"},
        {"Animated project PNG is unsupported", "不支持动画 PNG 项目"},

        // ---- Export options ------------------------------------------------------
        {"Format", "格式"},
        {"Encoded size", "编码尺寸"},
        {"JPEG quality", "JPEG 质量"},
        {"JPEG background", "JPEG 背景色"},

        // ---- Adjustments / filters ------------------------------------------------
        {"Adjustment preview; click to sample, drag for targeted hue adjustment",
         "调整预览；单击取样，拖动进行局部色相调整"},
        {"Sample original", "采样原图"},
        {"Original image", "原图"},
        {"Histogram weighted by opacity and selection", "按不透明度与选区加权的直方图"},
        {"Hue range before and after spectrum with four band handles",
         "调整前后的色相范围，带四个色带控制点"},
        {"Curves input and output graph", "曲线输入与输出图表"},
        {"Hue band handle angles", "色带控制点角度"},
        {"Click to add a point. Drag to adjust.", "单击添加控制点，拖动进行调整。"},
        {"Remove point", "移除控制点"},
        {"Reset curve", "重置曲线"},
        {"Add color", "添加颜色"},
        {"Remove color", "移除颜色"},
        {"Sample color", "颜色取样"},
        {"Targeted adjustment", "局部调整"},
        {"Color + neutral midtones", "彩色 + 中性灰"},
        {"Original RGB histogram and Levels handles", "原图 RGB 直方图与色阶控制点"},
        {"Linear histogram with automatic vertical scaling. Tall spikes may extend beyond the graph; all tones from 0 to 255 remain included.",
         "线性直方图，纵向自动缩放。较高的峰值可能超出图表范围；0 到 255 之间的所有色调均已包含。"},
        {"Loading histogram...", "正在加载直方图…"},
        {"Input black", "输入黑场"},
        {"Input white", "输入白场"},
        {"Output black", "输出黑场"},
        {"Output white", "输出白场"},
        {"Invalid Levels histogram", "无效的色阶直方图"},
        {"Invalid Levels preview source", "无效的色阶预览源"},
        {"Channel", "通道"},
        {"Range", "范围"},
        {"Applying adjustment\u2026", "正在应用调整\u2026"},
        {"Adjustment cancelled", "已取消调整"},
        {"Select an image layer", "请选择一个图像图层"},
        {"Reset Levels", "重置色阶"},
        {"Reset Hue/Saturation", "重置色相/饱和度"},
        {"Apply outside this range instead", "改为应用到此范围之外"},
        {"Color Picker (Gradient Map Highlights)", "颜色选择器（渐变映射高光）"},
        {"Color Picker (Gradient Map Shadows)", "颜色选择器（渐变映射阴影）"},
        {"Adjustment layer no longer exists", "调整图层已不存在"},
        {"Applying filter\u2026", "正在应用滤镜\u2026"},
        {"Filter cancelled", "已取消滤镜"},
        {"Completed filter target is missing", "滤镜目标缺失"},
        {"Unsupported filter kind", "不支持的滤镜类型"},
        {"Selection exceeds source allocation limits", "选区超出源分配上限"},
        {"The expanded filter mask exceeds its allocation budget", "扩展后的滤镜蒙版超出分配上限"},
        {"Selecting similar pixels\u2026", "正在选择相似像素\u2026"},

        // ---- Subject removal -------------------------------------------------------
        {"Remove Background", "移除背景"},
        {"Background removal preview", "背景移除预览"},
        {"Background removal is closed", "背景移除已关闭"},
        {"Finding foreground\u2026", "正在识别前景\u2026"},
        {"Applying mask\u2026", "正在应用蒙版\u2026"},
        {"No foreground", "未找到前景"},
        {"No foreground subject was detected. Try an image with a more distinct subject.",
         "未检测到前景主体。请尝试主体更清晰的图像。"},
        {"Background removal could not be completed. Try a smaller image or reopen the app.",
         "无法完成背景移除。请尝试更小的图像或重新打开应用。"},
        {"Background removal could not load its runtime. Repair or reinstall Compositor.",
         "背景移除无法加载运行时。请修复或重新安装 Compositor。"},
        {"Works best with a distinct, opaque subject. Transparent objects, fine hair and fur may need manual mask cleanup.",
         "适用于主体清晰、不透明的图像。透明物体、细发与毛发可能需要手动清理蒙版。"},
        {"Shift Edge", "边缘偏移"},
        {"The background removal document is no longer available", "背景移除文档已不可用"},
        {"The background removal target is no longer available", "背景移除目标已不可用"},
        {"The background removal source changed", "背景移除源已更改"},
        {"Subject preview target is missing", "主体预览目标缺失"},
        {"The background mask exceeds the project mask budget", "背景蒙版超出项目蒙版上限"},
        {"The background mask exceeds the refinement memory budget", "背景蒙版超出精修内存上限"},
        {"Existing mask dimensions differ", "现有蒙版尺寸不一致"},
        {"Image/mask size mismatch", "图像与蒙版尺寸不匹配"},

        // ---- Layer merge ------------------------------------------------------------
        {"Merge Layers", "合并图层"},
        {"The source layers changed; the prepared merge was not applied",
         "源图层已更改，预准备的合并未应用"},
        {"Incomplete merge host", "合并宿主不完整"},
        {"Other layers use the selected layers as clipping sources.",
         "其他图层正在使用所选图层作为剪贴来源。"},

        // ---- Mask actions -------------------------------------------------------------
        {"Add Layer Mask", "添加图层蒙版"},
        {"Add Mask from Selection", "从选区添加蒙版"},
        {"Add Reveal-All Mask", "添加全显示蒙版"},
        {"Add Hide-All Mask", "添加全隐藏蒙版"},
        {"Enable Layer Mask", "启用图层蒙版"},
        {"Disable Layer Mask", "停用图层蒙版"},
        {"Delete Layer Mask", "删除图层蒙版"},
        {"Link Layer Mask", "链接图层蒙版"},
        {"Unlink Layer Mask", "取消链接图层蒙版"},
        {"Copy Layer Mask", "复制图层蒙版"},
        {"Replace Layer Mask", "替换图层蒙版"},
        {"Layer Mask", "图层蒙版"},
        {"Gradient Mask", "渐变蒙版"},
        {"Fill Mask", "填充蒙版"},
        {"Blur Mask", "模糊蒙版"},
        {"Mask exceeds image limits", "蒙版超出图像限制"},
        {"Selection coverage is unavailable", "选区覆盖不可用"},
        {"Load Layer Selection", "加载图层选区"},
        {"Load Mask Selection", "加载蒙版选区"},

        // ---- Layer panel messages ------------------------------------------------------
        {"Dragged layer no longer exists", "拖动的图层已不存在"},
        {"Drop target is not a group", "拖放目标不是组"},
        {"Drop target no longer exists", "拖放目标已不存在"},
        {"Layer cannot be dropped here", "图层不能拖放到此处"},
        {"Folder duplication is not supported by this source operation",
         "此源操作不支持文件夹复制"},
        {"Invalid thumbnail box", "无效的缩略图框"},

        // ---- Update panel ---------------------------------------------------------------
        {"Check for Updates", "检查更新"},
        {"Update status", "更新状态"},
        {"Update progress", "更新进度"},
        {"Preparing update check\u2026", "正在准备检查更新\u2026"},
        {"Checking for a signed update\u2026", "正在检查签名更新\u2026"},
        {"Installing and verifying the signed update\u2026", "正在安装并验证签名更新\u2026"},
        {"Cancelling the update operation\u2026", "正在取消更新操作\u2026"},
        {"Verifying files and testing the installed version\u2026",
         "正在验证文件并测试已安装的版本\u2026"},
        {"Check again", "重新检查"},
        {"Install Update", "安装更新"},
        {"Restart Compositor", "重启 Compositor"},
        {"No newer update is available.", "没有可用的新版本。"},
        {"This version is already installed.", "此版本已安装。"},
        {"Update installed. Restart Compositor when you are ready.",
         "更新已安装。请在就绪后重启 Compositor。"},
        {"The installed update is ready. Restart Compositor when you are ready.",
         "已安装的更新已就绪。请在就绪后重启 Compositor。"},
        {"Restart cancelled. The installed update remains ready for the next launch.",
         "已取消重启。已安装的更新将在下次启动时继续就绪。"},
        {"Automatic updates are not configured for this preview. Install a new MSI or extract a new portable download to update Compositor.",
         "此预览版未配置自动更新。请安装新的 MSI 或解压新的便携版以更新 Compositor。"},
        {"Running version: ", "当前版本："},
        {"Retained previous version: ", "保留的上一版本："},
        {"Update cancelled. Active installed version: ", "更新已取消。当前安装版本："},
        {"Update cancelled. The active installed version could not be read. ",
         "更新已取消。无法读取当前安装版本。"},
        {"Updates are not configured for this development build. No update source is configured, and production updates are not available.",
         "此开发版本未配置更新。未配置更新源，也无法获取正式版更新。"},
        {"Updates are not configured for this development build. The installation version is invalid.",
         "此开发版本未配置更新。安装版本无效。"},
        {"Updates are not configured for this development build. This copy is not in a versioned installation.",
         "此开发版本未配置更新。当前副本不在版本化安装中。"},
        {"Development updates require schema 1, a testFeed, and explicit allowTestKey: true",
         "开发更新需要 schema 1、testFeed 以及显式的 allowTestKey: true"},
        {"Signed development update source. Production updates are not configured.",
         "已签名的开发更新源。未配置正式版更新。"},
        {"Update configuration is not a JSON object", "更新配置不是 JSON 对象"},
        {"Update configuration must be an ordinary file", "更新配置必须是普通文件"},
        {"Update source has an invalid length or contains a null character",
         "更新源长度无效或包含空字符"},
        {"Cannot read the bounded update configuration", "无法读取受限的更新配置"},
        {"Cannot locate the update installation root", "无法定位更新安装根目录"},

        // ---- Visual style / window controls --------------------------------------------
        {"Use colored window controls on the left. Turn off for the native Windows title bar.",
         "在左侧使用彩色窗口控制按钮。关闭则使用 Windows 原生标题栏。"},
        {"Close window", "关闭窗口"},
        {"Minimize window", "最小化窗口"},

        // ---- Miscellaneous status / errors ---------------------------------------------
        {"Alt-click where Clone Stamp should copy from first.",
         "请先按住 Alt 键单击仿制图章的取样位置。"},
        {"Use Blur to retouch a mask. Clone, Healing, Smudge and Liquify edit image pixels.",
         "使用模糊修饰蒙版。仿制图章、修复、涂抹和液化用于编辑图像像素。"},
        {"Point Sample", "点采样"},
        {"No active retouch target", "没有活动的修饰目标"},
        {"Invalid existing raster extent", "现有栅格范围无效"},
        {"Existing layers exceed the retouch pixel budget", "现有图层超出修饰像素上限"},
        {"The retouch target changed during the stroke", "笔划过程中修饰目标已更改"},
        {"Retouch did not produce a commit snapshot", "修饰未生成提交快照"},
        {"Using software retouch coverage: ", "使用软件修饰覆盖："},
        {"Using software brush: ", "使用软件画笔："},
        {"Dragged layer no longer exists", "拖动的图层已不存在"},
        {"The edit target no longer exists", "编辑目标已不存在"},
        {"The gradient target changed during preview", "预览过程中渐变目标已更改"},
        {"The duplicate target was removed", "复制目标已被移除"},
        {"The transform mask was removed", "变换蒙版已被移除"},
        {"The selected pixel target was removed", "所选像素目标已被移除"},
        {"The project path is not an existing directory", "项目路径不是现有目录"},
        {"Invalid RGBA buffer stride or storage", "RGBA 缓冲区步长或存储无效"},
        {"RGBA buffer is not premultiplied", "RGBA 缓冲区不是预乘格式"},
        {"Foreground preprocessing exceeds working buffer budget",
         "前景预处理超出工作缓冲区上限"},
        {"Invalid guided filter shape or radius", "导向滤波器形状或半径无效"},
        {"Guided filter epsilon must be positive", "导向滤波器的 epsilon 必须为正数"},
        {"Mask and guide dimensions differ", "蒙版与引导图尺寸不一致"},
        {"Guided matte exceeds transient memory budget", "导向抠图超出临时内存上限"},
        {"Cannot locate Windows color profiles", "无法定位 Windows 色彩配置文件"},
        {"Cannot locate Windows sRGB profile", "无法定位 Windows sRGB 配置文件"},
        {"Cannot locate the sRGB profile", "无法定位 sRGB 配置文件"},
        {"Cannot open encoded image for export", "无法打开编码图像进行导出"},
        {"Cannot read encoded image", "无法读取编码图像"},
        {"Cannot write encoded image", "无法写入编码图像"},
        {"Cannot flush exported image", "无法刷新导出的图像"},
        {"Atomic export replacement failed", "原子导出替换失败"},
        {"Cannot create temporary export beside destination", "无法在目标位置旁创建临时导出文件"},
        {"Cannot name temporary export", "无法命名临时导出文件"},
        {"Commit export container", "提交导出容器"},
        {"Commit export frame", "提交导出帧"},
        {"Incomplete layer-copy host", "图层复制宿主不完整"},
        {"Incomplete workspace drop host", "工作区拖放宿主不完整"},
        {"Workspace drop completion callback threw", "工作区拖放完成回调抛出异常"},
        {"Copy destination control is unavailable", "复制目标控件不可用"},
        {"Move Selection", "移动选区"},
        {"Move Pixels", "移动像素"},
        {"Move Layer", "移动图层"},
        {"Duplicate Pixels", "复制像素"},
        {"Expand Selection", "扩展选区"},
        {"Contract Selection", "收缩选区"},
        {"Expand pixels", "扩展像素"},
        {"Contract pixels", "收缩像素"},
        {"Select All", "全选"},
        {"Magic Wand", "魔棒"},
        {"New Blank Layer", "新建空白图层"},
        {"New selection", "新建选区"},
        {"Shape Style", "形状样式"},
        {"Layer Blend Mode", "图层混合模式"},
        {"Layer Opacity", "图层不透明度"},
        {"Layer Visibility", "图层可见性"},
        {"Crop", "裁剪"},
        {"Rename Layer", "重命名图层"},
        {"Flip Horizontal", "水平翻转"},
        {"Flip Vertical", "垂直翻转"},
        {"Flip Canvas Horizontal", "水平翻转画布"},
        {"Flip Canvas Vertical", "垂直翻转画布"},
        {"Delete Layers", "删除图层"},
        {"Hide Layer", "隐藏图层"},
        {"Show Layer", "显示图层"},
        {"Edit image", "编辑图像"},
        {"Edit mask", "编辑蒙版"},
        {"Width", "宽度"},
        {"Height", "高度"},
        {"Angle", "角度"},
        {"Distance", "距离"},
        {"Size", "大小"},
        {"Hardness", "硬度"},
        {"Opacity", "不透明度"},
        {"Mask", "蒙版"},
        {"Preview", "预览"},
        {"Image canvas", "图像画布"},
        {"New selection", "新建选区"},
        {"Create Texture", "创建纹理"},
        {"Proximity Match", "邻近匹配"},

        // ---- Blend modes (combo entries come from the shared enum table) -----
        {"Normal", "正常"},
        {"Dissolve", "溶解"},
        {"Darken", "变暗"},
        {"Multiply", "正片叠底"},
        {"Color Burn", "颜色加深"},
        {"Linear Burn", "线性加深"},
        {"Darker Color", "深色"},
        {"Lighten", "变亮"},
        {"Screen", "滤色"},
        {"Color Dodge", "颜色减淡"},
        {"Linear Dodge (Add)", "线性减淡（添加）"},
        {"Lighter Color", "亮色"},
        {"Overlay", "叠加"},
        {"Soft Light", "柔光"},
        {"Hard Light", "强光"},
        {"Vivid Light", "亮光"},
        {"Linear Light", "线性光"},
        {"Pin Light", "点光"},
        {"Hard Mix", "实色混合"},
        {"Difference", "差值"},
        {"Exclusion", "排除"},
        {"Subtract", "减去"},
        {"Divide", "划分"},
        {"Hue", "色相"},
        {"Saturation", "饱和度"},
        {"Color", "颜色"},
        {"Luminosity", "明度"},
        {"Freeform", "任意"},

        // ---- Transform sampling ------------------------------------------
        {"Nearest", "邻近"},
        {"Smooth", "平滑"},
        {"High quality", "高质量"},

        // ---- Project titles -------------------------------------------------
        {"Untitled", "未命名"},
        {"Untitled %1", "未命名 %1"},

        // ---- Dialog button boxes ---------------------------------------------
        {"OK", "确定"},
        {"Cancel", "取消"},
        {"Close", "关闭"},
        {"Apply", "应用"},
        {"Save", "保存"},
        {"Discard", "放弃"},
        {"Yes", "是"},
        {"No", "否"},
        {"Reset", "重置"},
    };
    return map;
}

} // namespace

QString zh(const QString& english) {
    if (english.isEmpty()) return english;
    const auto& map = table();
    // Exact match first.
    if (const auto it = map.constFind(english); it != map.constEnd()) return it.value();
    // Mnemonic form: "&File" may be spelled differently at the call site.
    if (english.contains('&')) {
        const QString bare = english;
        QString stripped = bare;
        stripped.remove('&');
        if (const auto it = map.constFind(stripped); it != map.constEnd())
            return applyMnemonic(bare, it.value());
    }
    // Trailing/leading whitespace tolerant match.
    const QString trimmed = english.trimmed();
    if (trimmed != english) {
        if (const auto it = map.constFind(trimmed); it != map.constEnd()) return it.value();
    }
    return english;
}

QString zh(const char* english) {
    if (!english) return {};
    return zh(QString::fromUtf8(english));
}

const char* zhc(const QString& english) {
    // The returned pointer stays valid until the next zhc() call on this
    // thread; every caller copies the value immediately.
    static thread_local std::string storage;
    storage = zh(english).toStdString();
    return storage.c_str();
}

const char* zhc(const char* english) {
    if (!english) return nullptr;
    return zhc(QString::fromUtf8(english));
}

QMenu* addCommandMenu(QMenuBar* bar, const QString& englishTitle) {
    auto* menu = bar->addMenu(zh(englishTitle));
    menu->setProperty("commandMenu", englishTitle);
    return menu;
}

QMenu* addCommandMenu(QMenu* parent, const QString& englishTitle) {
    auto* menu = parent->addMenu(zh(englishTitle));
    menu->setProperty("commandMenu", englishTitle);
    return menu;
}

} // namespace compositor::ui