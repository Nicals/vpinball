# 3.16 picked from Qt documentation:
# https://doc.qt.io/qt-6/cmake-get-started.html#building-a-c-gui-application
cmake_minimum_required(VERSION 3.16)

project(vpinball-editor
  VERSION 0.0.0
  LANGUAGES C CXX
)

find_package(Qt6 REQUIRED
  COMPONENTS Core Concurrent Widgets
)

qt_standard_project_setup()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)

# Have every built executable and shared library put in the build directory.
# This is needed because the VPinball lib is currently built $ORIGIN rpath.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)
