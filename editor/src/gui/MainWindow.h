#pragma once

#include <QMainWindow>
#include <qmainwindow.h>

#include <Editor.h>


namespace vpin::editor {

   class MainWindow final
      : public QMainWindow
   {
      Q_OBJECT

      public:
         explicit MainWindow(Editor* editor, QWidget* parent = nullptr);

      private:
         void buildFileMenuBar();
         void buildEditMenuBar();

      public slots:
         void loadTable();
         void openTableMetaDialog();
         void openSettingsDialog();
         void quitApplication();

      private:
         Editor* m_editor;
   };

}
