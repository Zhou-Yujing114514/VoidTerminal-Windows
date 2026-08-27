#ifndef WIN32_WINDOW_H_
#define WIN32_WINDOW_H_

#include <Windows.h>

#include <functional>
#include <memory>
#include <string>

// A Win32 window abstraction used to host a Flutter view.
class Win32Window {
 public:
  struct Point {
    unsigned int x = 0;
    unsigned int y = 0;
  };

  struct Size {
    unsigned int width = 0;
    unsigned int height = 0;
  };

  Win32Window();
  virtual ~Win32Window();

  // Creates and shows a Win32 window with the given |title|, |size| and
  // |origin|. Returns true if the window was created successfully.
  bool Create(const std::wstring &title, const Size &size, const Point &origin,
              HINSTANCE instance);

  // Show the window.
  void Show(int show_command);

  // Runs the main message loop, blocking until the window is closed.
  void Run(int show_command);

  // Called when the window is created. Override to perform setup.
  virtual void OnCreate();

  // Called when the window is destroyed. Override to clean up.
  virtual void OnDestroy();

  // Called when a message is received. Override to handle custom messages.
  // Return nullopt to let the base class handle the message.
  virtual LRESULT MessageHandler(HWND window, UINT const message,
                                 WPARAM const wparam, LPARAM const lparam);

  // Returns the HWND associated with this window.
  HWND GetHandle() const { return window_handle_; }

 protected:
  // Subclasses should override this to create the Flutter view controller.
  // Called from OnCreate.
  virtual void CreateFlutterView();

  HWND window_handle_ = nullptr;
  HINSTANCE instance_ = nullptr;

 private:
  static LRESULT CALLBACK WndProc(HWND const window, UINT const message,
                                  WPARAM const wparam, LPARAM const lparam);
};

#endif  // WIN32_WINDOW_H_
