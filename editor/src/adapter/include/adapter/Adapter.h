#pragma once

#include <string>


namespace vpin::editor {

   class Table;

   class Adapter
   {
      public:
         virtual ~Adapter() = default;

         virtual Table* loadTable(const std::string& filepath) = 0;
   };

}
