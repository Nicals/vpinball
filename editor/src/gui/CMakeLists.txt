find_package(Qt6 REQUIRED
  COMPONENTS Widgets
)

qt_standard_project_setup()

qt_add_executable(editor
  main.cpp
  MainWindow.cpp
)

target_link_libraries(editor
  PRIVATE Qt6::Widgets
)
