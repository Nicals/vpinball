#include <QApplication>
#include <QThread>

#include <utils/Logger.h>

#include <vpinball/VPinballAdapter.h>
#include <Editor.h>
#include <MainWindow.h>


int main(int argc, char* argv[])
{
   vpin::adapter::VPinballAdapter* adapter = new vpin::adapter::VPinballAdapter();
   adapter->setThreadCount(QThread::idealThreadCount());

   auto logger = Logger::GetInstance();
   logger->Init();
   logger->SetupLogger(true);

   vpin::editor::Editor* editor = new vpin::editor::Editor(adapter);

   QApplication::setOrganizationName("Visual Pinball");
   QApplication::setApplicationName("VPinball editor");
   QApplication app(argc, argv);

   vpin::editor::MainWindow window(editor);
   window.show();

   return app.exec();
}
