#pragma once

#include <QObject>
#include <QUuid>


namespace vpin::adapter {
   class Table;
}


namespace vpin::editor
{

   class TableEdit final
      : public QObject
   {
      Q_OBJECT;

      public:
         TableEdit(const QUuid& id, vpin::adapter::Table* table, QObject* parent = nullptr);
         ~TableEdit();

         const QUuid& getId() const;
         bool isDirty() const;

         void setName(const QString& name);
         QString getName() const;

      signals:
         void dirtyStateChanged(bool);
         void nameChanged(QString);

      private:
         void markDirty();

         QUuid m_id;
         bool m_dirty = false;
         vpin::adapter::Table* m_table;
   };

}
