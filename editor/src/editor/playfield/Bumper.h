#pragma once

#include "PlayfieldElement.h"


namespace vpin {
   namespace adapter {
      class Bumper;
   }

   namespace editor {

   class Bumper
      : public PlayfieldElement
   {
      Q_OBJECT;

      public:
         Bumper(adapter::Bumper* m_bumper, QObject* parent = nullptr);

         QPointF getPosition() const override;

      private:
         adapter::Bumper* m_bumper;
   };

   }
}
