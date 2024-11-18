#include <QApplication>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>

#include "dialogs/SettingsDialog.h"
#include "MainWindow.h"

namespace vpin::editor {

   MainWindow::MainWindow(Editor* editor, QWidget* parent)
      : m_editor{editor},
        QMainWindow(parent)
   {
      m_editor->setParent(this);
      buildFileMenuBar();
      buildEditMenuBar();
   }

   void MainWindow::buildFileMenuBar()
   {
      QAction* openTableAction = new QAction(tr("&Open table"));
      openTableAction->setShortcut(Qt::CTRL | Qt::Key_O);
      connect(openTableAction, &QAction::triggered, this, &MainWindow::loadTable);

      QAction* saveAction = new QAction(tr("Save"));
      saveAction->setShortcut(Qt::CTRL | Qt::Key_S);
      saveAction->setDisabled(!m_editor->hasTableLoaded());
      connect(m_editor, &Editor::tableLoaded, saveAction, [saveAction]() {
         saveAction->setEnabled(true);
      });

      QAction* saveAsAction = new QAction(tr("Save as"));
      saveAsAction->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_S);
      saveAsAction->setDisabled(!m_editor->hasTableLoaded());
      connect(m_editor, &Editor::tableLoaded, saveAsAction, [saveAsAction]() {
         saveAsAction->setEnabled(true);
      });

      QAction* quitAction = new QAction(tr("Quit"));
      quitAction->setShortcut(Qt::CTRL | Qt::Key_Q);
      connect(quitAction, &QAction::triggered, this, &MainWindow::quitApplication, Qt::QueuedConnection);

      QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
      fileMenu->addAction(openTableAction);
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

   void MainWindow::loadTable()
   {
      QString filepath = QFileDialog::getOpenFileName(
         this, tr("Open VPX file"), QString(), "VPX tables (*.vpx)"
      );

      if (filepath.isEmpty()) {
         return;
      }

      if (m_editor->loadTable(filepath)) {
         statusBar()->showMessage(tr("Loaded table: %1").arg(filepath));
      }
      else
      {
         QMessageBox::critical(this, tr("Error"), tr("Failed to load vpx table %1").arg(filepath));
      }
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
