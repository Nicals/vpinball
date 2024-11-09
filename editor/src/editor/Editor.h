#pragma once

#include <QObject>


namespace vpin::editor {

   class Editor final
      : public QObject
   {
      Q_OBJECT

      public:
         bool loadTable(const QString& filepath);
         bool hasTableLoaded() const;

      signals:
         void tableLoaded();

      private:
         bool m_loaded = false;
   };
}
