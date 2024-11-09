#include <QApplication>
#include <QCoreApplication>
#include <QMenuBar>

#include "MainWindow.h"

namespace vpin::editor {

   MainWindow::MainWindow(QWidget* parent)
      : QMainWindow(parent)
   {
      buildMenuBar();
   }

   MainWindow::~MainWindow()
   {
   }

   void MainWindow::buildMenuBar()
   {
      QAction* newAction = new QAction("New");
      newAction->setShortcut(Qt::CTRL | Qt::Key_N);
      QAction* saveAction = new QAction("Save");
      saveAction->setShortcut(Qt::CTRL | Qt::Key_S);
      QAction* saveAsAction = new QAction("Save as");
      saveAsAction->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_S);

      QAction* quitAction = new QAction("Quit");
      quitAction->setShortcut(Qt::CTRL | Qt::Key_Q);
      connect(quitAction, &QAction::triggered, this, &MainWindow::quitApplication, Qt::QueuedConnection);

      QMenu* fileMenu = menuBar()->addMenu("&File");
      fileMenu->addAction(newAction);
      fileMenu->addAction(saveAction);
      fileMenu->addAction(saveAsAction);
      fileMenu->addSeparator();
      fileMenu->addAction(quitAction);
   }

   void MainWindow::quitApplication()
   {
      qApp->quit();
   }
}
