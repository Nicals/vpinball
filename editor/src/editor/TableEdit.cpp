#include <adapter/Table.h>
#include <qobject.h>

#include "playfield/Bumper.h"
#include "TableEdit.h"


namespace vpin::editor {

   TableEdit::TableEdit(const QUuid& id, vpin::adapter::Table* table, QObject* parent)
      : m_id{id},
        m_table{table},
        QObject{parent}
   {
      for (auto bumper: table->getBumpers()) {
         m_elements.push_back(new Bumper(bumper, this));
      }
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

   void TableEdit::commit()
   {
      if (!m_dirty) {
         return;
      }

      m_dirty = false;
      emit dirtyStateChanged(false);
   }

   const QString& TableEdit::getFilepath() const
   {
      return m_filepath;
   }

   void TableEdit::setFilepath(const QString& filepath)
   {
      m_filepath = filepath;
   }

   void TableEdit::prepareForClosing()
   {
      emit aboutToClose();
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

   const QList<PlayfieldElement*>& TableEdit::getElements() const
   {
      return m_elements;
   }

   void TableEdit::markDirty()
   {
      if (m_dirty) {
         return;
      }

      m_dirty = true;
      emit dirtyStateChanged(true);
   }

}
