#include <TableEdit.h>

#include "TableBlueprint.h"


namespace vpin::editor {

   TableBlueprint::TableBlueprint(TableEdit* table, QWidget* parent)
      : m_table{table},
        QWidget{parent}
   {
   }

}
