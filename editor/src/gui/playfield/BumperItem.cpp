#include <QtMath>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <playfield/Bumper.h>
#include <playfield/PlayfieldTheme.h>
#include <qmath.h>

#include "DragHandle.h"
#include "BumperItem.h"


namespace vpin::editor {

   BumperItem::BumperItem(PlayfieldTheme* theme, Bumper* bumper)
      : m_theme{theme},
        m_bumper{bumper}
   {
      m_radiusHandle = new DragHandle{m_theme, this};
      m_radiusHandle->setPos(
         bumper->getRadius() * qCos(qDegreesToRadians(bumper->getOrientation())),
         bumper->getRadius() * qSin(qDegreesToRadians(bumper->getOrientation()))
      );

      setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
   }

   QRectF BumperItem::boundingRect() const
   {
      const float radius = m_bumper->getRadius();
      return QRectF{-radius, -radius, radius * 2, radius * 2};
   }

   void BumperItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
   {
      // Paint center
      painter->setPen(m_theme->getHandlePen(isSelected()));
      painter->setBrush(m_theme->getHandleBrush(isSelected()));
      painter->drawEllipse(QRectF{-10.0, -10.0, 20.0, 20.0});

      // Paint radius
      const float radius = m_bumper->getRadius();
      painter->setPen(m_theme->getRadiusPen());
      painter->drawEllipse(QRectF{-radius, -radius, radius * 2, radius * 2});
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
