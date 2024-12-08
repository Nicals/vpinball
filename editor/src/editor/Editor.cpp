#include <QDebug>
#include <QUndoGroup>

#include <adapter/Adapter.h>
#include <adapter/Table.h>

#include "Editor.h"
#include "TableEdit.h"
#include "playfield/PlayfieldTheme.h"


namespace vpin::editor {

   Editor::Editor(vpin::adapter::Adapter* adapter)
      : m_adapter{adapter},
        QObject()
   {
      m_theme = new PlayfieldTheme{this};
      m_undoGroup = new QUndoGroup;
   }

   Editor::~Editor()
   {
      delete m_adapter;
      for (auto table: m_tables) {
         delete table;
      }
   }

   PlayfieldTheme* Editor::getPlayfieldTheme()
   {
      return m_theme;
   }

   QUndoGroup* Editor::getUndoGroup()
   {
      return m_undoGroup;
   }

   bool Editor::loadTable(const QString& filepath)
   {
      TableEdit* table = new TableEdit(
         QUuid::createUuid(),
         m_adapter->loadTable(filepath.toStdString()),
         this
      );
      m_undoGroup->addStack(table->getUndoStack());
      table->setFilepath(filepath);
      m_tables.insert(table->getId(), table);

      qDebug() << "Table" << table->getName()
         << "has been loaded and registered as"
         << table->getId().toString(QUuid::WithoutBraces);

      emit tableCountChanged(m_tables.count());
      setActiveTable(table->getId());

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

   void Editor::closeTable(const QUuid& tableId)
   {
      TableEdit* table = getTable(tableId);
      qInfo() << "Closing table" << tableId << ":" << table->getName();
      m_undoGroup->removeStack(table->getUndoStack());
      table->prepareForClosing();

      m_tables.take(tableId);
      emit tableClosed();
      emit tableCountChanged(m_tables.count());
      qCritical() << "Closing table is not implemented on adapter side.";
   }

   TableEdit* Editor::getActiveTable() const
   {
      if (m_activeTable.isNull()) {
         qCritical() << "Cannot get active table: no active table yet.";
         return nullptr;
      }

      if (!m_tables.contains(m_activeTable)) {
         qCritical() << "Cannot get active table: table" << m_activeTable << "is not registered.";
         return nullptr;
      }

      return m_tables.value(m_activeTable);
   }

   void Editor::setActiveTable(const QUuid& id)
   {
      if (!m_tables.contains(id)) {
         qCritical() << "Cannot set active table: table" << m_activeTable << "is not registred.";
      }

      m_activeTable = id;
      m_undoGroup->setActiveStack(m_tables.value(id)->getUndoStack());
      emit activeTableChanged(id);
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

   bool Editor::hasPendingChanges() const
   {
      for (TableEdit* table: m_tables.values()) {
         if (table->isDirty()) {
            return true;
         }
      }

      return false;
   }

}
