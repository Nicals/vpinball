#include <adapter/Table.h>
#include <qobject.h>

#include "TableEdit.h"


namespace vpin::editor {

   TableEdit::TableEdit(const QUuid& id, vpin::adapter::Table* table, QObject* parent)
      : m_id{id},
        m_table{table},
        QObject{parent}
   {
   }

   TableEdit::~TableEdit()
   {
      delete m_table;
   }

   const QUuid& TableEdit::getId() const
   {
      return m_id;
   }

   bool TableEdit::isDirty() const
   {
      return m_dirty;
   }

   void TableEdit::setName(const QString& name)
   {
      m_table->setName(name.toStdString());

      emit nameChanged(name);
      markDirty();
   }

   QString TableEdit::getName() const
   {
      return QString::fromStdString(m_table->getName());
   }

   void TableEdit::markDirty()
   {
      bool wasDirty = m_dirty;
      m_dirty = true;

      if (!wasDirty) {
         emit dirtyStateChanged(true);
      }
   }

}
