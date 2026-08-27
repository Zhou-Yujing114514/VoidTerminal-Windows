# 虚空终端 Windows 桌面版（VoidTerminal-Windows）

虚空终端（聊天网站 buer.kdns.fr）的 Windows 原生桌面客户端，基于 Flutter 构建，原生渲染（非 WebView 套壳），连接 buer.kdns.fr。

与 [Linux 版](https://github.com/Zhou-Yujing114514/VoidTerminal-Linux) 共享同一套 Dart 业务逻辑（`lib/`），仅平台宿主层不同（Linux 用 GTK，Windows 用 Win32），界面与功能 1:1 对齐。

## 功能

- 登录 / 注册
- 全局大厅聊天
- 好友私聊、群聊
- 好友管理（加好友、好友申请）
- 群聊搜索、申请加入、创建群
- 朋友圈（发布、点赞、评论）
- 深色主题
- 管理员功能（公告、清空大厅）

## 技术栈

- Flutter（Dart）
- http、web_socket_channel、provider
- 平台宿主：Win32（C++）

## 环境要求

- Windows 10 / 11（x64）
- [Flutter SDK](https://docs.flutter.dev/get-started/install/windows)（>= 3.0，`flutter doctor` 中 "Windows" 项打勾）
- Visual Studio 2022（含「使用 C++ 的桌面开发」工作负载）

确认环境：

```powershell
flutter doctor
flutter config --enable-windows-desktop
```

## 安装（绿色版）

从 [Releases](https://github.com/Zhou-Yujing114514/VoidTerminal-Windows/releases) 下载 `VoidTerminal-Windows.zip`，解压后直接运行 `void_terminal_windows.exe` 即可，无需安装。

## 构建

### 方式一：使用构建脚本（推荐）

```powershell
# Release 构建
.\scripts\build_win.ps1

# 或指定构建类型：Debug / Release / Profile
.\scripts\build_win.ps1 -BuildType Release
```

也可用批处理脚本：

```cmd
scripts\build_win.bat
scripts\build_win.bat Release
```

### 方式二：手动构建

```powershell
# 首次克隆后，补齐 Windows 平台支持（会自动刷新 windows/ 宿主代码）
flutter create . --platforms=windows --project-name=void_terminal_windows

# 获取依赖
flutter pub get

# 构建 Release
flutter build windows --release
```

产物在 `build\windows\release\bundle\void_terminal_windows.exe`。

### 一键打包（PowerShell 压缩为 zip）

```powershell
$ErrorActionPreference='Stop'
flutter build windows --release
Compress-Archive -Force -Path "build\windows\release\bundle\*" -DestinationPath "VoidTerminal-Windows.zip"
```

## 目录结构

```
VoidTerminal-Windows/
├── lib/                # 共享 Dart 业务逻辑（与 Linux 版完全一致）
├── windows/            # Windows 平台宿主（CMake + Win32 C++）
│   ├── CMakeLists.txt
│   ├── flutter/
│   └── runner/
├── scripts/            # 构建脚本（build_win.bat / build_win.ps1）
└── pubspec.yaml
```

## 相关项目

- 网页版：https://buer.kdns.fr
- Linux 客户端：https://github.com/Zhou-Yujing114514/VoidTerminal-Linux
- Android 客户端：https://github.com/Zhou-Yujing114514/VoidTerminal-Android
- iOS 客户端：https://github.com/Zhou-Yujing114514/VoidTerminal-iOS
- 小说下载站：https://morax.kdns.fr
