#pragma once

#include "TableElement.h"


namespace vpin::adapter {

   class Bumper
      : public virtual TableElement
   {
      public:
         virtual ~Bumper() = default;
   };
}
