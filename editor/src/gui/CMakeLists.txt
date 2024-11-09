find_package(Qt6 REQUIRED
  COMPONENTS Widgets
)

qt_standard_project_setup()

qt_add_executable(editor
  main.cpp
  MainWindow.cpp
  dialogs/SettingsDialog.cpp
  widgets/PathEdit.cpp
)
qt_add_resources(editor icons
  PREFIX "/icons"
  BASE ./resources/icons/svgs/
  FILES
    ./resources/icons/svgs/regular/folder-open.svg
)

target_link_libraries(editor
  PRIVATE Qt6::Widgets
)
