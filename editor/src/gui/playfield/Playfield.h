#pragma once

#include <QGraphicsView>


namespace vpin::editor
{

   class TableEdit;

   class Playfield
      : public QGraphicsView
   {
      public:
         Playfield(TableEdit* table, QWidget* parent=nullptr);

      private:
         QGraphicsScene* m_scene;
         TableEdit* m_table;
   };
}
