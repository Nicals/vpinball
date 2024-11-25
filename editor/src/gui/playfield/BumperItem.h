#pragma once

#include <QGraphicsItem>

#include <playfield/Bumper.h>


namespace vpin::editor {

   class Bumper;
   class DragHandle;

   class BumperItem
      : public QGraphicsItem
   {
      public:
         BumperItem(Bumper* bumper);

         QRectF boundingRect() const override;
         void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

      private:
         Bumper* m_bumper;

         DragHandle* m_radiusHandle;
   };

}
