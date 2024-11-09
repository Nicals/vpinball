#include "Editor.h"


namespace vpin::editor {

   bool Editor::loadTable(const QString& filepath)
   {
      emit tableLoaded();
      return true;
   }

   bool Editor::hasTableLoaded() const
   {
      return m_loaded;
   }

}
