# Builds FFMPeg library exposing a ffmpeg target.

include(ExternalProject)

ExternalProject_Add(ffmpeg_build
  URL https://github.com/FFmpeg/FFmpeg/archive/b08d7969c550a804a59511c7b83f2dd8cc0499b8.zip
  DOWNLOAD_NO_PROGRESS ON
  CONFIGURE_COMMAND
    <SOURCE_DIR>/configure
      --enable-shared
      --disable-static
      --disable-programs
      --disable-doc
      --prefix=<INSTALL_DIR>
)
ExternalProject_Get_Property(ffmpeg_build INSTALL_DIR)

add_library(ffmpeg INTERFACE)
add_dependencies(ffmpeg ffmpeg_build)

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
