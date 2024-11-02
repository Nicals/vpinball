# Build libpinmame libraries. Exposes a pinmame target

include(ExternalProject)


# Cannot use FetchContent since CMakeLists files are not named as expected
# by cmake :(
ExternalProject_Add(pinmame_build
  URL https://github.com/vpinball/pinmame/archive/65cdbf58bc7be6ef414ea273d1bb8d4cb42471c8.zip
  DOWNLOAD_NO_PROGRESS ON
  CMAKE_ARGS
    -D CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
  PATCH_COMMAND ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/cmake/libpinmame/CMakeLists_linux-x64.txt <SOURCE_DIR>/CMakeLists.txt
  INSTALL_COMMAND ${CMAKE_COMMAND} -E make_directory <INSTALL_DIR>/include <INSTALL_DIR>/lib
    COMMAND ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/src/libpinmame/libpinmame.h <INSTALL_DIR>/include/
    COMMAND ${CMAKE_COMMAND} -E copy <BINARY_DIR>/libpinmame.so <INSTALL_DIR>/lib/
    COMMAND ${CMAKE_COMMAND} -E copy <BINARY_DIR>/libpinmame.so.3.6 <INSTALL_DIR>/lib/
)

ExternalProject_Get_Property(pinmame_build INSTALL_DIR)

add_library(pinmame INTERFACE)
add_dependencies(pinmame pinmame_build)

target_link_libraries(pinmame INTERFACE ${INSTALL_DIR}/lib/libpinmame.so)
target_include_directories(pinmame INTERFACE ${INSTALL_DIR}/include/)
