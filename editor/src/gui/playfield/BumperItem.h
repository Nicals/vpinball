#pragma once

#include <QGraphicsObject>

#include <Angle.h>

#include "ItemFactory.h"


namespace vpin::editor {

   class DragHandle;
   class PlayfieldTheme;
   class TableEdit;

   class BumperItem
      : public QGraphicsObject
   {
      Q_OBJECT;

      public:
         BumperItem(PlayfieldTheme* theme);

         void setRadius(float radius);
         void setOrientation(const Angle& degrees);

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
         Angle m_orientation;
   };

   class BumperItemFactory final
      : public ItemFactory
   {
      public:
         BumperItemFactory(TableEdit* table, PlayfieldTheme* theme);
         virtual ~BumperItemFactory() override = default;

         virtual QGraphicsObject* createGraphicsObject(PlayfieldElement* element) const override;

      private:
         PlayfieldTheme* m_theme;
         TableEdit* m_table;
   };

}
