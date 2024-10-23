# Builds FreeImage static library. Sets a 'freeimage' target library.

include(ExternalProject)

find_program(MAKE_EXECUTABLE NAMES make gmake nmake)

ExternalProject_Add(freeimage_build
  URL https://downloads.sourceforge.net/project/freeimage/Source%20Distribution/3.18.0/FreeImage3180.zip
  URL_HASH SHA1=38daa9d8f1bca2330a2eaa42ec66fbe6ede7dce9
  DOWNLOAD_NO_PROGRESS ON
  STEP_TARGETS install
  PATCH_COMMAND
    sed -i 
      -e "/^CXXFLAGS ?=/a CXXFLAGS += -std=c++11"
      -e "/^CFLAGS ?=/a CFLAGS += -Wno-implicit-function-declaration"
      <SOURCE_DIR>/Makefile.gnu
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ${MAKE_EXECUTABLE} -C <SOURCE_DIR> -f Makefile.gnu -j $(nproc)
  INSTALL_COMMAND
    # Manual installation since FreeImage 'install' Makefile target forces
    # root user on installed files. We only care about current user, not root.
    mkdir -p <BINARY_DIR>/include <BINARY_DIR>/lib
    COMMAND cp <SOURCE_DIR>/Dist/FreeImage.h <BINARY_DIR>/include/.
    COMMAND cp <SOURCE_DIR>/Dist/libfreeimage.a <BINARY_DIR>/lib/.
)
ExternalProject_Get_Property(freeimage_build BINARY_DIR)

add_library(freeimage INTERFACE)
add_dependencies(freeimage freeimage_build-install)

target_link_libraries(freeimage
  INTERFACE ${BINARY_DIR}/lib/libfreeimage.a
)
target_include_directories(freeimage
  INTERFACE ${BINARY_DIR}/include/
)
