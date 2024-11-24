#pragma once

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

      signals:
         void changed();

      private:
         QString m_name;
   };

}
