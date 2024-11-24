#pragma once

#include <string>

#include "Point.h"


namespace vpin::adapter
{

   class TableElement
   {
      public:
         virtual ~TableElement() = default;

         virtual void setName(const std::string& name) = 0;
         virtual std::string getName() = 0;

         virtual const Point2D getPosition() const = 0;
         virtual void setPosition(const Point2D& point) = 0;
   };

}
