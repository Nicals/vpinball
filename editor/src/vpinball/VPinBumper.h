#pragma once

#include <adapter/Bumper.h>

#include "VPinTableElement.h"


class Bumper;

namespace vpin::adapter {

   class VPinBumper final
      : public Bumper,
        public VPinTableElement
   {
      public:
         VPinBumper(::Bumper* bumper);

         const Point2D getPosition() const override;
         void setPosition(const Point2D& point) override;

      private:
         ::Bumper* m_bumper;
   };

}
