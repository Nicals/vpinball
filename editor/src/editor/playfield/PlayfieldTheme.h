#pragma once

#include <QObject>
#include <QPen>


namespace vpin::editor {

   /**
    * Holds pens and brushes to be used when drawing playfield elements.
    */
   class PlayfieldTheme
      : public QObject
   {
      Q_OBJECT;

      public:
         PlayfieldTheme(QObject* parent = nullptr);

         QPen getRadiusPen() const;

         QPen getHandlePen(bool isSelected = false) const;
         QBrush getHandleBrush(bool isSelected = false) const;

      signals:
         void changed();
   };

}
