#include <QDebug>

#include <adapter/Adapter.h>
#include <adapter/Table.h>
#include <quuid.h>

#include "Editor.h"
#include "TableEdit.h"


namespace vpin::editor {

   Editor::Editor(vpin::adapter::Adapter* adapter)
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
      TableEdit* table = new TableEdit(
         QUuid::createUuid(),
         m_adapter->loadTable(filepath.toStdString()),
         this
      );
      table->setFilepath(filepath);
      m_tables.insert(table->getId(), table);

      qDebug() << "Table" << table->getName()
         << "has been loaded and registered as"
         << table->getId().toString(QUuid::WithoutBraces);

      emit tableLoaded(table->getId());

      return true;
   }

   bool Editor::saveTable(const QUuid& tableId, const QString& filepath)
   {
      TableEdit* table = getTable(tableId);

      if (filepath.isEmpty()) {
         qCritical() << "Cannot save to empty filepath";
         return false;
      }

      qCritical() << "Saving tables is not yet implemented";
      table->setFilepath(filepath);
      table->commit();

      return true;
   }

   unsigned int Editor::getTableCount() const
   {
      return m_tables.size();
   }

   bool Editor::hasTableLoaded() const
   {
      return !m_tables.isEmpty();
   }

   TableEdit* Editor::getTable(const QUuid& id)
   {
      if (!m_tables.contains(id)) {
         qFatal() << "Accessing unknown table" << id;
      }

      return m_tables[id];
   }

}
