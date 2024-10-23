# Same minimum version as previously defined in this project.
# We may be able to decrease it if necessary.
cmake_minimum_required(VERSION 3.25)

# Actual path to vpinball root directory.
# XXX: We can revert to CMAKE_SOURCE_DIR if this build system is ever
#      merged into the project root directory.
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH VPIN_SOURCE_DIR)
# XXX: For debug purpose, remove this when ready
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Cmake modules
include(FetchContent)
# Our modules
include(VPinball)

get_vpinball_version(vpinball_version)


project(VisualPinball
  VERSION ${vpinball_version}
  DESCRIPTION "An open source pinball table editor and simulator."
  HOMEPAGE_URL https://github.com/vpinball/vpinball/
  LANGUAGES C CXX
)


# User options definition
option(POST_BUILD_COPY_EXT_LIBS "Copy external libraries to build directory." ON)

# Language requirements
# According to the book 'Professional CMake: A practical guide' it is recommended
# to set all three requirements variable (see 16.1).
# I'm not sure about the value of *_EXTENSIONS, it may be wrong. ON seems to
# be the default value ?
# We might need to investigate this futher
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


# External libraries
# TODO: Extract versions from existing standalone external.sh scripts for
#       the time being. This will allow us to rebase the branch and keep
#       track of any version change


set(SDL_OPENGLES OFF)
set(SDL_TEST_LIBRARY OFF)
FetchContent_Declare(sdl
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG preview-3.1.3
)

set(SDLIMAGE_VENDORED ON)
set(SDLIMAGE_AVIF OFF)
set(SDLIMAGE_WEBP OFF)
FetchContent_Declare(sdl_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG a010117fee88255a32492ae9a43e93a213d608ec
)

set(SDLTTF_VENDORED ON)
set(SDLTTF_HARFBUZZ ON)
FetchContent_Declare(sdl_ttf
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
  GIT_TAG b61b50ea756576382cc1ccf12491f7ebeab6eed1
)

include(FreeImage)

## Vpinball

add_subdirectory(dependencies/altsound)
add_subdirectory(dependencies/ffmpeg)

FetchContent_MakeAvailable(sdl sdl_image sdl_ttf)

# Quick smoke test to ensure lib dependencies are properly built
add_executable(smoke_test smoke.cpp)
target_link_libraries(smoke_test
  PRIVATE
    ffmpeg
    freeimage
    altsound
    SDL3-shared
    SDL3_image-shared
    SDL3_ttf-shared
)
