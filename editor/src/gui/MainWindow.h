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
         ~MainWindow();

      private:
         void buildMenuBar();

      public slots:
         void quitApplication();
   };

}
