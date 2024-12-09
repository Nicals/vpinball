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
         // Set the table opened in tab at given index as the active table.
         // Does nothing if the index is invalid.
         void activateTabTable(int index) const;

         // Creates a new tab for a given table.
         // Returns the index of the added tab
         int createNewTableTab(TableEdit* table);

         // Set the current tab as being the one managing the given table.
         // If no tab holds the given table, a new tab is created.
         // Nothing is done if tableId is a nullId
         void setCurrentTableTab(const QUuid& tableId);

      private:
         // Returns the index of the widget containing the given table. -1 if not found.
         int findTableWidget(const QUuid& id) const;

      private:
         Editor* m_editor;
   };

}
