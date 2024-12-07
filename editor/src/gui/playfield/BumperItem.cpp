#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <playfield/Bumper.h>
#include <playfield/PlayfieldTheme.h>

#include "DragHandle.h"
#include "BumperItem.h"


namespace vpin::editor {

   BumperItem::BumperItem(PlayfieldTheme* theme, Bumper* bumper)
      : m_theme{theme},
        m_bumper{bumper}
   {
      m_radiusHandle = new DragHandle{m_theme, this};
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
      painter->setPen(m_theme->getHandlePen(isSelected()));
      painter->setBrush(m_theme->getHandleBrush(isSelected()));
      painter->drawEllipse(QRectF{-10.0, -10.0, 20.0, 20.0});

      // Paint radius
      const float radius = m_bumper->getRadius();
      painter->setPen(m_theme->getRadiusPen());
      painter->drawEllipse(QRectF{-radius, -radius, radius * 2, radius * 2});
   }

}
