#pragma once

#include <QGraphicsObject>


namespace vpin::editor {

   class DragHandle;
   class PlayfieldTheme;

   class BumperItem
      : public QGraphicsObject
   {
      Q_OBJECT;

      public:
         BumperItem(PlayfieldTheme* theme);

         void setRadius(float radius);
         void setOrientation(float degrees);

         QRectF boundingRect() const override;
         void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

      protected:
         void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
         QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

      private:
         void updateRadiusHandle();

      signals:
         void hasBeenMoved(QPointF position);

      private:
         PlayfieldTheme* m_theme;

         DragHandle* m_radiusHandle;

         float m_radius = 0;
         // Stored in radians
         float m_orientation = 0;
   };

}
