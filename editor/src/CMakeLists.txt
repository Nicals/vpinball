add_subdirectory(adapter)
add_subdirectory(editor)
add_subdirectory(gui)
add_subdirectory(vpinball)

add_library(plog INTERFACE)
target_include_directories(plog INTERFACE ../../third-party/include/plog)

qt_add_executable(vpinball_editor
  main.cpp
  PlogBridge.cpp
)

target_link_libraries(vpinball_editor PRIVATE adapter::vpinball gui plog vpinball)

set_target_properties(vpinball_editor PROPERTIES
  OUTPUT_NAME VPinball-editor
)
