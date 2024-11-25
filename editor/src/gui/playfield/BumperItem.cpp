#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <playfield/Bumper.h>

#include "DragHandle.h"
#include "BumperItem.h"


namespace vpin::editor {

   BumperItem::BumperItem(Bumper* bumper)
      : m_bumper{bumper}
   {
      m_radiusHandle = new DragHandle{this};
      m_radiusHandle->setPos(bumper->getRadius(), 0.0);
   }

   QRectF BumperItem::boundingRect() const
   {
      const float radius = m_bumper->getRadius();
      return QRectF{-radius, -radius, radius * 2, radius * 2};
   }

   void BumperItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
   {
      // Paint center
      {
         if (isSelected()) {
            painter->setPen(QPen(Qt::red));
         }

         painter->drawEllipse(QRectF{-10.0, -10.0, 20.0, 20.0});
      }

      // Paint radius
      {
         const float radius = m_bumper->getRadius();
         QPen radiusPen{QColor{0x22cc22}};
         radiusPen.setStyle(Qt::DashLine);

         painter->setPen(radiusPen);
         painter->drawEllipse(QRectF{-radius, -radius, radius * 2, radius * 2});
      }
   }

}
