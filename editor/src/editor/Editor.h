#pragma once

#include <QMap>
#include <QUuid>
#include <QObject>
#include <quuid.h>

namespace vpin::adapter {
   class Adapter;
}

namespace vpin::editor {

   class TableEdit;

   class Editor final
      : public QObject
   {
      Q_OBJECT

      public:
         Editor(vpin::adapter::Adapter* adapter);
         ~Editor();

         bool loadTable(const QString& filepath);
         unsigned int getTableCount() const;
         bool hasTableLoaded() const;
         TableEdit* getTable(const QUuid& id);

      signals:
         void tableLoaded(const QUuid&);

      private:
         vpin::adapter::Adapter* m_adapter;

         QMap<QUuid, TableEdit*> m_tables;
         bool m_loaded = false;
   };
}
