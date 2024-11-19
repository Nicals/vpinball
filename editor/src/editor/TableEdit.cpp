#include <adapter/Table.h>
#include <qobject.h>

#include "TableEdit.h"


namespace vpin::editor {

   TableEdit::TableEdit(vpin::adapter::Table* table, QObject* parent)
      : m_table{table},
        QObject{parent}
   {
   }

   TableEdit::~TableEdit()
   {
      delete m_table;
   }

   bool TableEdit::isDirty() const
   {
      return m_dirty;
   }

   void TableEdit::setName(const QString& name)
   {
      m_table->setName(name.toStdString());
      m_dirty = true;

      emit nameChanged(name);
   }

   QString TableEdit::getName() const
   {
      return QString::fromStdString(m_table->getName());
   }

}
