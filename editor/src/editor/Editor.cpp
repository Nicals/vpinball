#include <adapter/Adapter.h>
#include <adapter/Table.h>

#include "Editor.h"
#include "TableEdit.h"


namespace vpin::editor {

   Editor::Editor(Adapter* adapter)
      : m_adapter{adapter},
        QObject()
   {
   }

   Editor::~Editor()
   {
      delete m_adapter;
      for (auto table: m_tables) {
         delete table;
      }
   }

   bool Editor::loadTable(const QString& filepath)
   {
      bool startedEmpty = m_activeTable == nullptr;

      m_activeTable = new TableEdit(m_adapter->loadTable(filepath.toStdString()), this);
      m_tables.push_back(m_activeTable);

      if (startedEmpty) {
         emit tableLoaded();
      }
      emit activeTableChanged();

      return true;
   }

   bool Editor::hasTableLoaded() const
   {
      return m_activeTable != nullptr;
   }

   TableEdit* Editor::getActiveTable()
   {
      if (m_activeTable == nullptr) {
         qCritical("Accessing active table without any loaded table.");
      }

      return m_activeTable;
   }

}
