#include <QApplication>
#include <QCommandLineParser>
#include <QThread>

#include <utils/Logger.h>

#include <vpinball/VPinballAdapter.h>
#include <Editor.h>
#include <MainWindow.h>


int main(int argc, char* argv[])
{
   QTextStream err(stderr);

   QApplication::setOrganizationName("Visual Pinball");
   QApplication::setApplicationName("VPinball editor");
   QApplication app(argc, argv);

   QCommandLineParser parser;
   parser.setApplicationDescription("VPinball editor");
   parser.addPositionalArgument("file", "Optional table file to load.");
   parser.addOptions({
      {{"h", "help"}, "Show this"},
   });

   parser.process(app);

   if (parser.isSet("h")) {
      parser.showHelp();
   }

   vpin::adapter::VPinballAdapter* adapter = new vpin::adapter::VPinballAdapter();
   adapter->setThreadCount(QThread::idealThreadCount());

   auto logger = Logger::GetInstance();
   logger->Init();
   logger->SetupLogger(true);

   vpin::editor::Editor* editor = new vpin::editor::Editor(adapter);
   vpin::editor::MainWindow window(editor);

   if (parser.positionalArguments().size() > 1) {
      err << "Too many files provided.\nUsage:\n";
      parser.showHelp(128);
   }
   if (!parser.positionalArguments().empty()) {
      editor->loadTable(parser.positionalArguments().first());
   }

   window.show();

   return app.exec();
}
