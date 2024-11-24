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

         void setName(const QString& name);
         const QString& getName() const;

         virtual QPointF getPosition() const = 0;

      signals:
         void changed();

      private:
         QString m_name;
   };

}
