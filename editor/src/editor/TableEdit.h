#pragma once

#include <QObject>


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
         TableEdit(vpin::adapter::Table* table, QObject* parent = nullptr);
         ~TableEdit();

         bool isDirty() const;

         void setName(const QString& name);
         QString getName() const;

      signals:
         void nameChanged(QString);

      private:
         bool m_dirty = false;
         vpin::adapter::Table* m_table;
   };

}
