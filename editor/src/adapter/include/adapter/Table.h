#pragma once

#include <string>


namespace vpin::editor
{

   class Table
   {
      public:
         virtual ~Table() = default;

         virtual void setName(const std::string& name) = 0;
         virtual std::string getName() const = 0;
   };

   void load_table(const std::string& filepath);

}
