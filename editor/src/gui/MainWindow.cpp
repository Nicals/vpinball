#include <QApplication>
#include <QCoreApplication>
#include <QMenuBar>
#include <QStatusBar>

#include "dialogs/SettingsDialog.h"
#include "MainWindow.h"

namespace vpin::editor {

   MainWindow::MainWindow(QWidget* parent)
      : QMainWindow(parent)
   {
      buildFileMenuBar();
      buildEditMenuBar();
   }

   void MainWindow::buildFileMenuBar()
   {
      QAction* newAction = new QAction(tr("New"));
      newAction->setShortcut(Qt::CTRL | Qt::Key_N);
      QAction* saveAction = new QAction(tr("Save"));
      saveAction->setShortcut(Qt::CTRL | Qt::Key_S);
      QAction* saveAsAction = new QAction(tr("Save as"));
      saveAsAction->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_S);

      QAction* quitAction = new QAction(tr("Quit"));
      quitAction->setShortcut(Qt::CTRL | Qt::Key_Q);
      connect(quitAction, &QAction::triggered, this, &MainWindow::quitApplication, Qt::QueuedConnection);

      QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
      fileMenu->addAction(newAction);
      fileMenu->addAction(saveAction);
      fileMenu->addAction(saveAsAction);
      fileMenu->addSeparator();
      fileMenu->addAction(quitAction);
   }

   void MainWindow::buildEditMenuBar()
   {
      QAction* settingsAction = new QAction(tr("Settings"));
      connect(settingsAction, &QAction::triggered, this, &MainWindow::openSettingsDialog);

      QMenu* menu = menuBar()->addMenu(tr("&Edit"));
      menu->addAction(settingsAction);
   }

   void MainWindow::openSettingsDialog()
   {
      SettingsDialog settingsDialog(this);
      settingsDialog.setModal(true);

      settingsDialog.exec();

      statusBar()->showMessage(tr("Settings have been saved."));
   }

   void MainWindow::quitApplication()
   {
      qApp->quit();
   }
}
