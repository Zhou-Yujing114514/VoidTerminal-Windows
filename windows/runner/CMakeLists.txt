cmake_minimum_required(VERSION 3.14)

set(BINARY_NAME "void_terminal_windows")

# Sources for the runner. C++17 is the minimum supported by Flutter.
set(RUNNER_SRCS
  "main.cpp"
  "flutter_window.cpp"
  "win32_window.cpp"
  "Runner.rc"
)

# Ensure the build uses C++17.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable.
add_executable(${BINARY_NAME} WIN32 ${RUNNER_SRCS})
apply_standard_settings(${BINARY_NAME})

# Add the Flutter engine as a dependency.
target_link_libraries(${BINARY_NAME} PRIVATE flutter)
target_link_libraries(${BINARY_NAME} PRIVATE "flutter_windows")
target_link_libraries(${BINARY_NAME} PRIVATE "winmm.lib" "user32.lib" "gdi32.lib"
  "shell32.lib" "advapi32.lib" "ws2_32.lib" "kernel32.lib" "comdlg32.lib"
  "shcore.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "imm32.lib" "version.lib"
  "pathcch.lib" "dwmapi.lib")

# Headers are located in the runner directory.
target_include_directories(${BINARY_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# Generated plugin registrant header.
target_include_directories(${BINARY_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/..")

# Set the application icon.
set_target_properties(${BINARY_NAME} PROPERTIES
  RC_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Runner.rc"
)
