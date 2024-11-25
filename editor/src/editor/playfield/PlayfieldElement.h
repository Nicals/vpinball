#pragma once

#include <QPointF>
#include <QObject>


namespace vpin::editor {

   class PlayfieldElement
      : public QObject
   {
      Q_OBJECT;

      public:
         PlayfieldElement(QObject* parent = nullptr);

         virtual void setName(const QString& name) = 0;
         virtual const QString getName() const = 0;

         virtual QPointF getPosition() const = 0;
         virtual void setPosition(QPointF position) = 0;

      signals:
         void changed();
   };

}
