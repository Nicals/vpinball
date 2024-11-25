#include <QPainter>

#include "DragHandle.h"


namespace vpin::editor {

   DragHandle::DragHandle(QGraphicsItem* parent)
      : QGraphicsItem{parent}
   {
   }

   QRectF DragHandle::boundingRect() const
   {
      return QRectF{-m_handleRadius / 2, -m_handleRadius / 2, m_handleRadius, m_handleRadius};
   }

   void DragHandle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
   {
      painter->drawEllipse(boundingRect());
   }

}
