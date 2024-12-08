#pragma once

#include <QMainWindow>

class QDockWidget;
class QUndoView;

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
         TableEdit* getActiveTable();

         void createUndoDock();

      public slots:
         void loadTable();
         bool saveCurrentTable();
         bool saveCurrentTableInNewFile();
         void closeActiveTable();

         void openTableMetaDialog();
         void openSettingsDialog();

         void undo();
         void redo();

         void showUndoDock(bool show);

         void quitApplication();

      private:
         Editor* m_editor;
         QTabWidget* m_tabs;

         // Dock widgets
         QDockWidget* m_undoDock;
         QUndoView* m_undoView;

         // Settings
         static const int tempMessageTimeout = 5e3;
   };

}
