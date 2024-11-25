#pragma once

#include <QGraphicsItem>


namespace vpin::editor {

   /**
    * An item that can be dragged around by the user.
    */
   class DragHandle
      : public QGraphicsItem
   {
      public:
         explicit DragHandle(QGraphicsItem* parent = nullptr);

         QRectF boundingRect() const override;
         void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

      private:
         qreal m_handleRadius = 10.;
   };
}
