#include <TableEdit.h>

#include "Playfield.h"


namespace vpin::editor {

   Playfield::Playfield(TableEdit* table, QWidget* parent)
      : m_table{table},
        QGraphicsView{parent}
   {
      m_scene = new QGraphicsScene;
      m_scene->addText("Hello scene");

      setScene(m_scene);
   }

}
