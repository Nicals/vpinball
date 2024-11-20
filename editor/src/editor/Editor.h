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
         bool saveTable(const QUuid& tableId, const QString& filepath);
         void closeTable(const QUuid& tableId);
         unsigned int getTableCount() const;
         bool hasTableLoaded() const;
         TableEdit* getTable(const QUuid& id);

      signals:
         void tableClosed();
         void tableLoaded(const QUuid&);
         void tableCountChanged(int);

      private:
         vpin::adapter::Adapter* m_adapter;

         QMap<QUuid, TableEdit*> m_tables;
         bool m_loaded = false;
   };
}
