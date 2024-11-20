#pragma once

#include <QTabWidget>


namespace vpin::editor {

   class Editor;

   class TableTabs final
      : public QTabWidget
   {
      public:
         TableTabs(Editor* editor, QWidget* parent = nullptr);

      public slots:
         void createNewTableTab(const QUuid& tableId);

      private:
         Editor* m_editor;
   };

}
