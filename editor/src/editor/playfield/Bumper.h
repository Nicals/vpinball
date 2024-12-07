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

         const QString getName() const override;
         void setName(const QString& name) override;

         QPointF getPosition() const override;
         void setPosition(QPointF position) override;
         float getRadius() const;
         void setRadius(float radius);
         float getOrientation() const;
         void setOrientation(float degrees);

      private:
         adapter::Bumper* m_bumper;
   };

   }
}
