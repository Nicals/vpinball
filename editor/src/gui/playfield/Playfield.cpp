#include <TableEdit.h>

#include <playfield/PlayfieldElement.h>
#include "PlayfieldGraphicsItem.h"
#include "Playfield.h"


namespace vpin::editor {

   Playfield::Playfield(TableEdit* table, QWidget* parent)
      : m_table{table},
        QGraphicsView{parent}
   {
      m_scene = new QGraphicsScene;

      setScene(m_scene);

      for (auto obj: m_table->getElements()) {
         QGraphicsItem* item = new PlayfieldGraphicsItem(obj);
         item->setPos(obj->getPosition());
         m_scene->addItem(item);
      }
   }

}
