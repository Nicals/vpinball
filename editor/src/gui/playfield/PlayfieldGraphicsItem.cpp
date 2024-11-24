#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "PlayfieldGraphicsItem.h"


namespace vpin::editor {

   PlayfieldGraphicsItem::PlayfieldGraphicsItem(PlayfieldElement* element)
      : m_element{element}
   {
   }

   QRectF PlayfieldGraphicsItem::boundingRect() const
   {
      return QRectF{-20.0, -20.0, 40.0, 40.0};
   }

   void PlayfieldGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
   {
      painter->drawEllipse(QRectF{-20.0, -20.0, 40.0, 40.0});
   }

}
