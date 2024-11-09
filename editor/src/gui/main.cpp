#include <QApplication>

#include "MainWindow.h"

#include <Editor.h>


int main(int argc, char* argv[])
{
   vpin::editor::Editor* editor = new vpin::editor::Editor();

   QApplication::setOrganizationName("Visual Pinball");
   QApplication::setApplicationName("VPinball editor");
   QApplication app(argc, argv);

   vpin::editor::MainWindow window(editor);
   window.show();

   return app.exec();
}
