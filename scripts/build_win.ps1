# ============================================================
#  VoidTerminal - Windows 构建脚本 (PowerShell)
#  用法:
#    .\build_win.ps1              # 默认 Release
#    .\build_win.ps1 -BuildType Debug
# ============================================================
param(
  [ValidateSet("Debug","Release","Profile")]
  [string]$BuildType = "Release"
)

Write-Host "[VoidTerminal] 构建类型: $BuildType" -ForegroundColor Cyan

# 检查 Flutter
if (-not (Get-Command flutter -ErrorAction SilentlyContinue)) {
  Write-Host "[错误] 未检测到 flutter 命令，请先安装 Flutter SDK 并加入 PATH。" -ForegroundColor Red
  Write-Host "       https://docs.flutter.dev/get-started/install/windows" -ForegroundColor Red
  exit 1
}

Write-Host "[VoidTerminal] 检测到 Flutter:" -ForegroundColor Cyan
flutter --version

# 补齐 Windows 平台支持（首次克隆后执行一次）
Write-Host "[VoidTerminal] 确保已启用 Windows 桌面支持..." -ForegroundColor Cyan
flutter create . --platforms=windows --project-name=void_terminal_windows 2>$null

# 拉取依赖
Write-Host "[VoidTerminal] 获取依赖..." -ForegroundColor Cyan
flutter pub get

# 构建
Write-Host "[VoidTerminal] 开始构建 $BuildType ..." -ForegroundColor Cyan
flutter build windows --$BuildType
if ($LASTEXITCODE -ne 0) {
  Write-Host "[错误] 构建失败。" -ForegroundColor Red
  exit 1
}

Write-Host ""
Write-Host "[VoidTerminal] 构建成功！" -ForegroundColor Green
Write-Host "  产物目录: build\windows\$BuildType\bundle" -ForegroundColor Green
Write-Host "  可执行文件: build\windows\$BuildType\bundle\void_terminal_windows.exe" -ForegroundColor Green
