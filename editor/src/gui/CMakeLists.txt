qt_add_library(gui STATIC
  MainWindow.cpp
  dialogs/SettingsDialog.cpp
  dialogs/TableMetaDialog.cpp
  widgets/PathEdit.cpp
)

qt_add_resources(gui icons
  PREFIX "/icons"
  BASE ./resources/icons/svgs/
  FILES
    ./resources/icons/svgs/regular/folder-open.svg
)

target_link_libraries(gui
  PUBLIC Qt6::Widgets editor
)

target_include_directories(gui INTERFACE .)
