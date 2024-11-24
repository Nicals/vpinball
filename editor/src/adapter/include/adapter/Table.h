#pragma once

#include <string>
#include <vector>


namespace vpin::adapter
{

   class TableElement;

   class Table
   {
      public:
         virtual ~Table() = default;

         virtual void setName(const std::string& name) = 0;
         virtual std::string getName() const = 0;

         std::vector<TableElement*> getElements();
   };

}
