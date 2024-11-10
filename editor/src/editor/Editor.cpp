#include <adapter/Table.h>

#include "Editor.h"


namespace vpin::editor {

   Editor::Editor()
      : QObject()
   {
   }

   bool Editor::loadTable(const QString& filepath)
   {
      load_table();
      emit tableLoaded();
      return true;
   }

   bool Editor::hasTableLoaded() const
   {
      return m_loaded;
   }

}
