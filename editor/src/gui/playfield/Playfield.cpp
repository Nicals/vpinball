#include <TableEdit.h>

#include "Playfield.h"


namespace vpin::editor {

   Playfield::Playfield(TableEdit* table, QWidget* parent)
      : m_table{table},
        QWidget{parent}
   {
   }

}
