qt_add_library(gui STATIC
  MainWindow.cpp
  TableTabs.cpp
)
add_subdirectory(dialogs)
add_subdirectory(playfield)
add_subdirectory(widgets)

qt_add_resources(gui icons
  PREFIX "/icons"
  BASE ./resources/icons/svgs/
  FILES
    ./resources/icons/svgs/regular/folder-open.svg
    ./resources/icons/svgs/solid/asterisk.svg
)

target_link_libraries(gui
  PUBLIC Qt6::Widgets editor
)

target_include_directories(gui INTERFACE .)
