@echo off
setlocal enabledelayedexpansion
rem ============================================================
rem  VoidTerminal - Windows 构建脚本
rem  用法:
rem    build_win.bat              (默认 Release)
rem    build_win.bat Debug
rem    build_win.bat Release
rem ============================================================

set BUILD_TYPE=%1
if "%BUILD_TYPE%"=="" set BUILD_TYPE=Release

echo [VoidTerminal] 构建类型: %BUILD_TYPE%

rem ---- 检查 Flutter 环境 ----
where flutter >nul 2>&1
if errorlevel 1 (
  echo [错误] 未检测到 flutter 命令，请先安装 Flutter SDK 并加入 PATH。
  echo        https://docs.flutter.dev/get-started/install/windows
  exit /b 1
)

echo [VoidTerminal] 检测到 Flutter:
flutter --version

rem ---- 补齐 Windows 平台支持（首次克隆后执行一次）----
echo [VoidTerminal] 确保已启用 Windows 桌面支持...
flutter create . --platforms=windows --project-name=void_terminal_windows >nul 2>&1

rem ---- 拉取依赖 ----
echo [VoidTerminal] 获取依赖...
flutter pub get

rem ---- 构建 ----
echo [VoidTerminal] 开始构建 %BUILD_TYPE% ...
flutter build windows --%BUILD_TYPE%

if errorlevel 1 (
  echo [错误] 构建失败。
  exit /b 1
)

echo.
echo [VoidTerminal] 构建成功！
echo   产物目录: build\windows\%BUILD_TYPE%\bundle
echo   可执行文件: build\windows\%BUILD_TYPE%\bundle\void_terminal_windows.exe
echo.
endlocal
