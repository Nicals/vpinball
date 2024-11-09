#include <QApplication>

#include "MainWindow.h"


int main(int argc, char* argv[])
{
   QApplication::setOrganizationName("Visual Pinball");
   QApplication::setApplicationName("VPinball editor");
   QApplication app(argc, argv);

   vpin::editor::MainWindow window;
   window.show();

   return app.exec();
}
