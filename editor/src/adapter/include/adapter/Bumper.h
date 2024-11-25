#pragma once

#include "TableElement.h"


namespace vpin::adapter {

   class Bumper
      : public virtual TableElement
   {
      public:
         virtual ~Bumper() = default;

         virtual float getRadius() const = 0;
         virtual void setRadius(float radius) = 0;
   };
}
