# This CMake file is a part of the Flutter tool.
#
# This file *should not* be edited. Instead, search/replace directives belong
# in the flutter/{projectName}_windows.dart_plugin_registrant.dart template,
# which will be used to regenerate this file.

cmake_minimum_required(VERSION 3.14)

set(FLUTTER_MANAGED_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# Flutter library directory.
set(FLUTTER_LIBRARY_DIR "${FLUTTER_MANAGED_DIR}/ephemeral")

# Flutter tool directory.
set(FLUTTER_TOOL_DIR "${FLUTTER_LIBRARY_DIR}/flutter_tools")

# Flutter target platform.
set(FLUTTER_TARGET_PLATFORM "windows-x64")

# System libraries.
set(FLUTTER_SYSTEM_LIBRARIES
  user32.lib
  gdi32.lib
  shell32.lib
  advapi32.lib
  ws2_32.lib
  kernel32.lib
  comdlg32.lib
  shcore.lib
  ole32.lib
  oleaut32.lib
  uuid.lib
  winmm.lib
  imm32.lib
  version.lib
  pathcch.lib
)

# Flutter library.
set(FLUTTER_LIBRARY "${FLUTTER_LIBRARY_DIR}/flutter_windows.dll.lib")

# Flutter ICU data file.
set(FLUTTER_ICU_DATA_FILE "${FLUTTER_LIBRARY_DIR}/icudtl.dat")

# Flutter AOT library (only used in release/profile builds).
set(AOT_LIBRARY "${FLUTTER_LIBRARY_DIR}/flutter_windows.dll.lib")

# Flutter build rules.
include("${FLUTTER_LIBRARY_DIR}/flutter_build_rules.cmake")
