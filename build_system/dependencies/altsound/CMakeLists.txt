# Build libaltsound libraries exposing an altsound target.

include(ExternalProject)
include(FetchContent)

ExternalProject_Add(altsound_build
  URL https://github.com/vpinball/libaltsound/archive/b8f397858cbc7a879f7392c14a509f00c8bdc7dd.zip
  DOWNLOAD_NO_PROGRESS ON
  CMAKE_ARGS
    -D PLATFORM=linux
    -D ARCH=x64
    -D BUILD_STATIC=OFF
    -D CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -D CMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Add_Step(altsound_build fetch_dependencies
  DEPENDEES update
  DEPENDERS build
  COMMENT Download bass24
  COMMAND curl -sL https://www.un4seen.com/files/bass24-linux.zip -o bass.zip
  COMMAND unzip -oj bass.zip bass.h -d <SOURCE_DIR>/third-party/include/
  COMMAND unzip -oj bass.zip libs/x86_64/libbass.so -d <SOURCE_DIR>/third-party/runtime-libs/linux/x64/
)

ExternalProject_Get_Property(altsound_build INSTALL_DIR)
ExternalProject_Get_Property(altsound_build SOURCE_DIR)

add_library(altsound INTERFACE)
add_dependencies(altsound altsound_build)

target_link_libraries(altsound INTERFACE
  ${INSTALL_DIR}/lib/libaltsound.so
  ${SOURCE_DIR}/third-party/runtime-libs/linux/x64/libbass.so
)
target_include_directories(altsound INTERFACE ${INSTALL_DIR}/include)
