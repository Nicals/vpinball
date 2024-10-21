# VPinball related functions

# Extracts VPinball version from source files and stores the version in <version_out> variable.
function(get_vpinball_version version_out)
  set(version_filepath ${VPIN_SOURCE_DIR}/src/core/vpversion.h)
  if(NOT EXISTS ${version_filepath})
    message(FATAL_ERROR "VPinball version file '${version_filepath}' was not found. Aborting.")
  endif()

  file(READ ${version_filepath} version_h)

  string(REGEX MATCH "VP_VERSION_MAJOR[ ]+([0-9]+)" _tmp ${version_h})
  set(version_major "${CMAKE_MATCH_1}")
  string(REGEX MATCH "VP_VERSION_MINOR[ ]+([0-9]+)" _tmp ${version_h})
  set(version_minor "${CMAKE_MATCH_1}")
  string(REGEX MATCH "VP_VERSION_REV[ ]+([0-9]+)" _tmp ${version_h})
  set(version_patch "${CMAKE_MATCH_1}")

  set(${version_out} ${version_major}.${version_minor}.${version_patch})
  return(PROPAGATE ${version_out})
endfunction()

