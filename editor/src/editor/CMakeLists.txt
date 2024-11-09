qt_add_library(vpin_adapter STATIC
  Editor.cpp
)

target_link_libraries(vpin_adapter PRIVATE Qt6::Core)
target_include_directories(vpin_adapter INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
