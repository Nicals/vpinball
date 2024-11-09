#pragma once

#include <QMainWindow>
#include <qmainwindow.h>


namespace vpin::editor {

   class MainWindow final
      : public QMainWindow
   {
      Q_OBJECT

      public:
         explicit MainWindow(QWidget* parent = nullptr);

      private:
         void buildFileMenuBar();
         void buildEditMenuBar();

      public slots:
         void openSettingsDialog();
         void quitApplication();
   };

}
