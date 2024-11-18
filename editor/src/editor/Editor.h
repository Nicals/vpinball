#pragma once

#include <QObject>

namespace vpin::editor {

   class Adapter;

   class Editor final
      : public QObject
   {
      Q_OBJECT

      public:
         Editor(Adapter* adapter);
         ~Editor();

         bool loadTable(const QString& filepath);
         bool hasTableLoaded() const;

      signals:
         void tableLoaded();

      private:
         Adapter* m_adapter;
         bool m_loaded = false;
   };
}
