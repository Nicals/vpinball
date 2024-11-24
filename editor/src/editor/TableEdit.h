#pragma once

#include <QObject>
#include <QList>
#include <QUuid>


namespace vpin::adapter {
   class Table;
}


namespace vpin::editor
{
   class PlayfieldElement;

   class TableEdit final
      : public QObject
   {
      Q_OBJECT;

      public:
         TableEdit(const QUuid& id, vpin::adapter::Table* table, QObject* parent = nullptr);
         ~TableEdit();

         const QUuid& getId() const;
         bool isDirty() const;
         void commit();
         const QString& getFilepath() const;
         void setFilepath(const QString& filepath);
         void prepareForClosing();

         void setName(const QString& name);
         QString getName() const;

      signals:
         void aboutToClose();
         void dirtyStateChanged(bool);
         void nameChanged(QString);

      private:
         void markDirty();

         QUuid m_id;
         bool m_dirty = false;
         QString m_filepath;

         vpin::adapter::Table* m_table;
         QList<PlayfieldElement*> m_elements;
   };

}
