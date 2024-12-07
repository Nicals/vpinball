#pragma once

#include <QGraphicsObject>


namespace vpin::editor {

   class Bumper;
   class DragHandle;
   class PlayfieldTheme;

   class BumperItem
      : public QGraphicsObject
   {
      Q_OBJECT;

      public:
         BumperItem(PlayfieldTheme* theme, Bumper* bumper);

         QRectF boundingRect() const override;
         void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

      protected:
         void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
         QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

      signals:
         void hasBeenMoved(QPointF position);

      private:
         PlayfieldTheme* m_theme;
         Bumper* m_bumper;

         DragHandle* m_radiusHandle;
   };

}
