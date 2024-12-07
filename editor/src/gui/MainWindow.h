#pragma once

#include <QMainWindow>


namespace vpin::editor {

   class Editor;
   class TableEdit;

   class MainWindow final
      : public QMainWindow
   {
      Q_OBJECT

      public:
         explicit MainWindow(Editor* editor, QWidget* parent = nullptr);

      private:
         void buildFileMenuBar();
         void buildEditMenuBar();
         TableEdit* getActiveTable();

      public slots:
         void loadTable();
         bool saveCurrentTable();
         bool saveCurrentTableInNewFile();
         void closeActiveTable();

         void openTableMetaDialog();
         void openSettingsDialog();

         void undo();
         void redo();

         void quitApplication();

      private:
         Editor* m_editor;
         QTabWidget* m_tabs;
   };

}
