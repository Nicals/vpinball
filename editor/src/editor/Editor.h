#pragma once

#include <vector>

#include <QObject>

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
         bool hasTableLoaded() const;
         TableEdit* getActiveTable();

      signals:
         void tableLoaded();
         void activeTableChanged();

      private:
         vpin::adapter::Adapter* m_adapter;

         std::vector<TableEdit*> m_tables;
         TableEdit* m_activeTable = nullptr;
         bool m_loaded = false;
   };
}
