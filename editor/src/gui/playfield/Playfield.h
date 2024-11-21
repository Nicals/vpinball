#pragma once

#include <QWidget>


namespace vpin::editor
{

   class TableEdit;

   class Playfield
      : public QWidget
   {
      public:
         Playfield(TableEdit* table, QWidget* parent=nullptr);

      private:
         TableEdit* m_table;
   };
}
