#include <adapter/Adapter.h>

#include "Editor.h"


namespace vpin::editor {

   Editor::Editor(Adapter* adapter)
      : m_adapter{adapter},
        QObject()
   {
   }

   Editor::~Editor()
   {
      delete m_adapter;
   }

   bool Editor::loadTable(const QString& filepath)
   {
      m_adapter->loadTable(filepath.toStdString());
      emit tableLoaded();
      return true;
   }

   bool Editor::hasTableLoaded() const
   {
      return m_loaded;
   }

}
