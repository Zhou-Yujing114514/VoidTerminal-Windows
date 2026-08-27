#include "flutter_window.h"

#include <optional>

#include "resource.h"
#include "utils.h"

FlutterWindow::FlutterWindow(HINSTANCE instance, const flutter::DartProject &project,
                             std::vector<std::string> &&command_line_arguments)
    : project_(project), command_line_arguments_(std::move(command_line_arguments)) {
  // Use a reasonable default size, matching the Linux client. The user can
  // resize at runtime.
  Win32Window::Size size = {1280, 800};
  Win32Window::Create("VoidTerminal", size, {}, instance);
}

FlutterWindow::~FlutterWindow() = default;

void FlutterWindow::OnCreate() {
  // No-op; engine is started by the base class once the window is created.
}

void FlutterWindow::OnDestroy() {
  flutter_controller_ = nullptr;
}

LRESULT FlutterWindow::MessageHandler(HWND window, UINT const message,
                                     WPARAM const wparam,
                                     LPARAM const lparam) noexcept {
  // Give Flutter, including plugins, an opportunity to handle the message.
  if (flutter_controller_) {
    std::optional<LRESULT> result =
        flutter_controller_->HandleTopLevelWindowProc(window, message, wparam,
                                                      lparam);
    if (result) {
      return *result;
    }
  }

  switch (message) {
    case WM_FONTCHANGE:
      flutter_controller_->Engine()->ReloadSystemFonts();
      return 0;
    default:
      break;
  }

  return Win32Window::MessageHandler(window, message, wparam, lparam);
}
