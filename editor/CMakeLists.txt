# 3.16 picked from Qt documentation:
# https://doc.qt.io/qt-6/cmake-get-started.html#building-a-c-gui-application
cmake_minimum_required(VERSION 3.16)

project(vpinball-editor
  VERSION 0.0.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
