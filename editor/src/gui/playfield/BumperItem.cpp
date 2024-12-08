#include <QtMath>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <playfield/Bumper.h>
#include <playfield/PlayfieldTheme.h>

#include "DragHandle.h"
#include "BumperItem.h"


namespace vpin::editor {

   BumperItem::BumperItem(PlayfieldTheme* theme)
      : m_theme{theme}
   {
      m_radiusHandle = new DragHandle{m_theme, this};

      setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
   }

   void BumperItem::setRadius(float radius)
   {
      m_radius = radius;
      updateRadiusHandle();
   }

   void BumperItem::setOrientation(float degrees)
   {
      m_orientation = qDegreesToRadians(degrees);
      updateRadiusHandle();
   }

   void BumperItem::updateRadiusHandle()
   {
      m_radiusHandle->setPos(
         m_radius * qCos(qDegreesToRadians(m_orientation)),
         m_radius * qSin(qDegreesToRadians(m_orientation))
      );
   }

   QRectF BumperItem::boundingRect() const
   {
      return QRectF{-m_radius, -m_radius, m_radius * 2, m_radius * 2};
   }

   void BumperItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
   {
      // Paint center
      painter->setPen(m_theme->getHandlePen(isSelected()));
      painter->setBrush(m_theme->getHandleBrush(isSelected()));
      painter->drawEllipse(QRectF{-10.0, -10.0, 20.0, 20.0});

      // Paint radius
      painter->setPen(m_theme->getRadiusPen());
      painter->drawEllipse(QRectF{-m_radius, -m_radius, m_radius * 2, m_radius * 2});
   }

   void BumperItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
   {
      QGraphicsItem::mouseReleaseEvent(event);

      emit hasBeenMoved(pos());
   }

   QVariant BumperItem::itemChange(GraphicsItemChange change, const QVariant& value)
   {
      if (change == GraphicsItemChange::ItemPositionChange) {
         // Prevent item to be moved to negative position
         QPointF newPosition = value.toPointF();
         if (newPosition.x() < 0) {
            newPosition.setX(0);
         }

         if (newPosition.y() < 0) {
            newPosition.setY(0);
         }

         return newPosition;
      }

      return QGraphicsItem::itemChange(change, value);
   }

}
