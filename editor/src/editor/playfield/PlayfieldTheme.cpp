#include "PlayfieldTheme.h"


namespace vpin::editor {

   PlayfieldTheme::PlayfieldTheme(QObject* parent)
      : QObject{parent}
   {
   }

   QPen PlayfieldTheme::getRadiusPen() const
   {
      QPen pen{QColor{0x22cc22}};
      pen.setStyle(Qt::DashLine);

      return pen;
   }

   QPen PlayfieldTheme::getHandlePen(bool isSelected) const
   {
      QPen pen;
      if (isSelected) {
         pen.setColor(Qt::red);
      }

      return pen;
   }

   QBrush PlayfieldTheme::getHandleBrush(bool isSelected) const
   {
      QBrush brush;
      return brush;
   }

}
