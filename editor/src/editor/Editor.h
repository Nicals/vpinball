#pragma once

#include <vector>

#include <QObject>

namespace vpin::editor {

   class Adapter;
   class TableEdit;

   class Editor final
      : public QObject
   {
      Q_OBJECT

      public:
         Editor(Adapter* adapter);
         ~Editor();

         bool loadTable(const QString& filepath);
         bool hasTableLoaded() const;
         TableEdit* getActiveTable();

      signals:
         void tableLoaded();
         void activeTableChanged();

      private:
         Adapter* m_adapter;

         std::vector<TableEdit*> m_tables;
         TableEdit* m_activeTable = nullptr;
         bool m_loaded = false;
   };
}
