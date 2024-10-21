# Builds FFMPeg library.

include(ExternalProject)

find_program(MAKE_EXECUTABLE NAMES make gmake nmake)

ExternalProject_Add(ffmpeg_build
  GIT_REPOSITORY https://github.com/FFmpeg/FFmpeg.git
  GIT_TAG b08d7969c550a804a59511c7b83f2dd8cc0499b8
  STEP_TARGETS install
  CONFIGURE_COMMAND
    <SOURCE_DIR>/configure
      --enable-shared
      --disable-static
      --disable-programs
      --disable-doc
      --prefix=<INSTALL_DIR>
)
ExternalProject_Get_Property(ffmpeg_build INSTALL_DIR)
file(GLOB ffmpeg_libs ${INSTALL_DIR}/lib/lib*.so*)

add_library(ffmpeg INTERFACE)
add_dependencies(ffmpeg ffmpeg_build-install)

target_link_libraries(ffmpeg
  INTERFACE
    ${INSTALL_DIR}/lib/libavcodec.so
    ${INSTALL_DIR}/lib/libavdevice.so
    ${INSTALL_DIR}/lib/libavfilter.so
    ${INSTALL_DIR}/lib/libavformat.so
    ${INSTALL_DIR}/lib/libavutil.so
    ${INSTALL_DIR}/lib/libswresample.so
    ${INSTALL_DIR}/lib/libswscale.so
)
target_include_directories(ffmpeg
  INTERFACE ${INSTALL_DIR}/include
)
