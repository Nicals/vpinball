#include <QApplication>
#include <QCommandLineParser>
#include <QLoggingCategory>
#include <QThread>

#include <vpinball/VPinballAdapter.h>
#include <Editor.h>
#include <MainWindow.h>

#include "PlogBridge.h"


void configureLogger(bool verbose=false)
{
   QStringList pattern;
   pattern << "%{time hh:mm:ss.zzz}"
      << "[%{type}]"
      << "[%{category}]";
   if (verbose) {
      pattern << "[%{function}::%{line}]";
   }
   pattern << "- %{message}";

   vpin::editor::bridgePlog();
   qSetMessagePattern(pattern.join(' '));

   QStringList filters;
   if (!verbose) {
      filters << "*.debug=false" << "*.info=false";
   }

   QLoggingCategory::setFilterRules(filters.join('\n'));
}


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
      {"verbose", "More verbose logs"},
      {{"h", "help"}, "Show this"},
   });

   parser.process(app);

   if (parser.isSet("help")) {
      parser.showHelp();
   }

   vpin::adapter::VPinballAdapter* adapter = new vpin::adapter::VPinballAdapter();
   adapter->setThreadCount(QThread::idealThreadCount());

   configureLogger(parser.isSet("verbose"));

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
