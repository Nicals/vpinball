#pragma once

#include <QGraphicsItem>


namespace vpin::editor {

   class PlayfieldElement;

   class PlayfieldGraphicsItem
      : public QGraphicsItem
   {
      public:
         PlayfieldGraphicsItem(PlayfieldElement* element);

         QRectF boundingRect() const override;
         void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

      private:
         PlayfieldElement* m_element;
   };

}
