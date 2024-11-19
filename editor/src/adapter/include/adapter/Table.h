#pragma once

#include <string>


namespace vpin::adapter
{

   class Table
   {
      public:
         virtual ~Table() = default;

         virtual void setName(const std::string& name) = 0;
         virtual std::string getName() const = 0;
   };

}
