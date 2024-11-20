#pragma once

#include <QWidget>


namespace vpin::editor
{

   class TableEdit;

   class TableBlueprint
      : public QWidget
   {
      public:
         TableBlueprint(TableEdit* table, QWidget* parent=nullptr);

      private:
         TableEdit* m_table;
   };
}
