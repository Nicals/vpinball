#pragma once

#include <Angle.h>

#include "ItemFactory.h"
#include "PlayfieldGraphicsObject.h"


namespace vpin::editor {

   class DragHandle;
   class PlayfieldTheme;
   class TableEdit;

   class BumperItem
      : public PlayfieldGraphicsObject
   {
      Q_OBJECT;

      public:
         BumperItem(PlayfieldElement* element, PlayfieldTheme* theme);

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

         virtual PlayfieldGraphicsObject* createGraphicsObject(PlayfieldElement* element) const override;

      private:
         PlayfieldTheme* m_theme;
         TableEdit* m_table;
   };

}
