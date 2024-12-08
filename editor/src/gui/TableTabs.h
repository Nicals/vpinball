#pragma once

#include <QTabWidget>


namespace vpin::editor {

   class Editor;
   class TableEdit;

   class TableTabs final
      : public QTabWidget
   {
      public:
         TableTabs(Editor* editor, QWidget* parent = nullptr);

      private slots:
         void createNewTableTab(TableEdit* table);

      private:
         // Returns the index of the widget containing the given table. -1 if not found.
         int findTableWidget(const QUuid& id) const;

      private:
         Editor* m_editor;
   };

}
