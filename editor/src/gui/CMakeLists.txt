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
  PRIVATE vpin_adapter Qt6::Widgets
)
