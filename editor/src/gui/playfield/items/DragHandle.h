#pragma once

#include <QGraphicsItem>


namespace vpin::editor {

   class PlayfieldTheme;

   /**
    * An item that can be dragged around by the user.
    */
   class DragHandle
      : public QGraphicsItem
   {
      public:
         explicit DragHandle(PlayfieldTheme* theme, QGraphicsItem* parent = nullptr);

         QRectF boundingRect() const override;
         void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

      private:
         PlayfieldTheme* m_theme;
         qreal m_handleRadius = 10.;
   };
}
