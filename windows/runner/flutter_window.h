#ifndef FLUTTER_WINDOW_H_
#define FLUTTER_WINDOW_H_

#include <flutter/dart_project.h>
#include <flutter/flutter_view_controller.h>

#include <memory>

#include "win32_window.h"

// A window that hosts a Flutter view.
class FlutterWindow : public Win32Window {
 public:
  // Creates a Flutter window hosting the given project.
  FlutterWindow(HINSTANCE instance, const flutter::DartProject &project,
                std::vector<std::string> &&command_line_arguments);
  virtual ~FlutterWindow();

 protected:
  // Win32Window:
  void OnCreate() override;
  void OnDestroy() override;
  LRESULT MessageHandler(HWND window, UINT const message, WPARAM const wparam,
                         LPARAM const lparam) noexcept override;

 private:
  // The project to run in this window.
  flutter::DartProject project_;

  // The command line arguments to pass to the Flutter engine.
  std::vector<std::string> command_line_arguments_;

  // The Flutter instance hosted by this window.
  std::unique_ptr<flutter::FlutterViewController> flutter_controller_;
};

#endif  // FLUTTER_WINDOW_H_
