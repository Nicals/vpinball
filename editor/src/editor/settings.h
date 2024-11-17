#pragma once

#include <string_view>


namespace vpin::editor {

   // This namespace contains keys used in editor settings.
   namespace settings {
      using namespace std::literals;

      // Location of VPinball executable
      constexpr auto vpinball_executable_path = "VPinballPath"sv;
   }

}
