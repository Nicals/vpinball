#pragma once

#include <QObject>


namespace vpin::editor
{
   class Table;

   class TableEdit final
      : public QObject
   {
      Q_OBJECT;

      public:
         TableEdit(Table* table, QObject* parent = nullptr);
         ~TableEdit();

         bool isDirty() const;

         void setName(const QString& name);
         QString getName() const;

      signals:
         void nameChanged(QString);

      private:
         bool m_dirty = false;
         Table* m_table;
   };

}
