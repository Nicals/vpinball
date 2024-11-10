qt_add_executable(gui
  main.cpp
  MainWindow.cpp
  dialogs/SettingsDialog.cpp
  widgets/PathEdit.cpp
)

qt_add_resources(gui icons
  PREFIX "/icons"
  BASE ./resources/icons/svgs/
  FILES
    ./resources/icons/svgs/regular/folder-open.svg
)

target_link_libraries(gui
  PRIVATE Qt6::Widgets editor
)

set_target_properties(gui PROPERTIES
  OUTPUT_NAME VPinball-editor
)
