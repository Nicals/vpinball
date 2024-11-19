add_subdirectory(adapter)
add_subdirectory(editor)
add_subdirectory(gui)
add_subdirectory(vpinball)

qt_add_executable(vpinball_editor
  main.cpp
)

target_link_libraries(vpinball_editor PRIVATE adapter::vpinball gui vpinball)

set_target_properties(vpinball_editor PROPERTIES
  OUTPUT_NAME VPinball-editor
)
