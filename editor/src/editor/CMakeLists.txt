qt_add_library(editor STATIC
  Editor.cpp
  TableEdit.cpp
)
add_subdirectory(playfield)

target_link_libraries(editor PRIVATE Qt6::Core PUBLIC adapter::interface)
target_include_directories(editor INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
