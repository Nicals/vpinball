#include <QPainter>

#include <playfield/PlayfieldTheme.h>

#include "DragHandle.h"


namespace vpin::editor {

   DragHandle::DragHandle(PlayfieldTheme* theme, QGraphicsItem* parent)
      : m_theme{theme},
        QGraphicsItem{parent}
   {
   }

   QRectF DragHandle::boundingRect() const
   {
      return QRectF{-m_handleRadius / 2, -m_handleRadius / 2, m_handleRadius, m_handleRadius};
   }

   void DragHandle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
   {
      painter->setPen(m_theme->getHandlePen());
      painter->setBrush(m_theme->getHandleBrush());
      painter->drawEllipse(boundingRect());
   }

}
