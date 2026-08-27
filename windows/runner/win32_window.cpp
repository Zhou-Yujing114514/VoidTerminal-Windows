#include "win32_window.h"

#include <dwmapi.h>
#include <flutter/flutter_view_controller.h>

#include <iostream>

#include "resource.h"
#include "utils.h"

namespace {

constexpr const wchar_t *kWindowClassName = L"VoidTerminalWindow";

}  // namespace

Win32Window::Win32Window() = default;
Win32Window::~Win32Window() = default;

void Win32Window::OnCreate() {}
void Win32Window::OnDestroy() {}

bool Win32Window::Create(const std::wstring &title, const Size &size,
                         const Point &origin, HINSTANCE instance) {
  instance_ = instance;

  WNDCLASS wc = {};
  wc.lpfnWndProc = WndProc;
  wc.hInstance = instance;
  wc.lpszClassName = kWindowClassName;
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wc.hIcon = LoadIcon(instance, MAKEINTRESOURCE(IDI_APP_ICON));
  RegisterClass(&wc);

  // Center the window on the primary monitor by default.
  int screen_width = GetSystemMetrics(SM_CXSCREEN);
  int screen_height = GetSystemMetrics(SM_CYSCREEN);
  int x = (screen_width - size.width) / 2;
  int y = (screen_height - size.height) / 2;

  HWND hwnd =
      CreateWindow(kWindowClassName, title.c_str(),
                   WS_OVERLAPPEDWINDOW | WS_VISIBLE, x, y, size.width,
                   size.height, nullptr, nullptr, instance, this);
  if (!hwnd) {
    return false;
  }

  // Enable per-monitor DPI awareness for crisp rendering on HiDPI displays.
  SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

  window_handle_ = hwnd;
  OnCreate();
  return true;
}

void Win32Window::Show(int show_command) {
  ShowWindow(window_handle_, show_command);
}

void Win32Window::Run(int show_command) {
  Show(show_command);
  MSG msg;
  while (GetMessage(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

LRESULT Win32Window::MessageHandler(HWND window, UINT const message,
                                    WPARAM const wparam, LPARAM const lparam) {
  switch (message) {
    case WM_DESTROY:
      window_handle_ = nullptr;
      OnDestroy();
      PostQuitMessage(0);
      return 0;
    default:
      return DefWindowProc(window, message, wparam, lparam);
  }
}

void Win32Window::CreateFlutterView() {
  // Intentionally empty; FlutterWindow::OnCreate may override.
}

LRESULT CALLBACK Win32Window::WndProc(HWND const window, UINT const message,
                                      WPARAM const wparam, LPARAM const lparam) {
  Win32Window *self = nullptr;
  if (message == WM_NCCREATE) {
    CREATESTRUCT *cs = reinterpret_cast<CREATESTRUCT *>(lparam);
    self = reinterpret_cast<Win32Window *>(cs->lpCreateParams);
    SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
    self->window_handle_ = window;
  } else {
    self = reinterpret_cast<Win32Window *>(
        GetWindowLongPtr(window, GWLP_USERDATA));
  }
  if (self) {
    return self->MessageHandler(window, message, wparam, lparam);
  }
  return DefWindowProc(window, message, wparam, lparam);
}
