#pragma once

#include <string>
#include <vector>


namespace vpin::adapter
{

   class Bumper;

   class Table
   {
      public:
         virtual ~Table() = default;

         virtual void setName(const std::string& name) = 0;
         virtual std::string getName() const = 0;

         virtual const std::vector<Bumper*> getBumpers() const = 0;
   };

}
