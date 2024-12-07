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
         // Orientations are in degrees
         virtual float getOrientation() const = 0;
         virtual void setOrientation(float degrees) = 0;
   };
}
