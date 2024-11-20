#include <QApplication>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>

#include <Editor.h>
#include <TableEdit.h>

#include "dialogs/SettingsDialog.h"
#include "dialogs/TableMetaDialog.h"
#include "MainWindow.h"
#include "TableTabs.h"

namespace vpin::editor {

   MainWindow::MainWindow(Editor* editor, QWidget* parent)
      : m_editor{editor},
        QMainWindow(parent)
   {
      m_editor->setParent(this);
      buildFileMenuBar();
      buildEditMenuBar();

      m_tabs = new TableTabs{m_editor};
      setCentralWidget(m_tabs);
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
      connect(saveAction, &QAction::triggered, this, &MainWindow::saveCurrentTable);

      QAction* saveAsAction = new QAction(tr("Save as"));
      saveAsAction->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_S);
      saveAsAction->setDisabled(!m_editor->hasTableLoaded());
      connect(m_editor, &Editor::tableLoaded, saveAsAction, [saveAsAction]() {
         saveAsAction->setEnabled(true);
      });
      connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveCurrentTableInNewFile);

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
      QAction* tableMetaAction = new QAction(tr("Table meta"));
      tableMetaAction->setDisabled(!m_editor->hasTableLoaded());
      connect(m_editor, &Editor::tableLoaded, tableMetaAction, [tableMetaAction]() {
         tableMetaAction->setEnabled(true);
      });
      connect(tableMetaAction, &QAction::triggered, this, &MainWindow::openTableMetaDialog);

      QAction* settingsAction = new QAction(tr("Settings"));
      connect(settingsAction, &QAction::triggered, this, &MainWindow::openSettingsDialog);

      QMenu* menu = menuBar()->addMenu(tr("&Edit"));
      menu->addAction(tableMetaAction);
      menu->addSeparator();
      menu->addAction(settingsAction);
   }

   TableEdit* MainWindow::getActiveTable()
   {
      QWidget* currentTab = m_tabs->currentWidget();
      if (currentTab == nullptr) {
         qCritical("Cannot open table meta dialog: no curent table.");
         return nullptr;
      }

      QVariant tableId = currentTab->property("tableId");
      if (!tableId.isValid()) {
         qCritical("Cannot open table meta dialog: current widget has no tableId property.");
         return nullptr;
      }

      return m_editor->getTable(tableId.value<QUuid>());
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

   void MainWindow::saveCurrentTable()
   {
      TableEdit* table = getActiveTable();
      if (table == nullptr) {
         return;
      }

      if (table->getFilepath().isEmpty()) {
         return saveCurrentTableInNewFile();
      }

      if (m_editor->saveTable(table->getId(), table->getFilepath())) {
         statusBar()->showMessage(tr("Table saved as %1").arg(table->getFilepath()));
      }
      else {
         QMessageBox::critical(this, tr("Error"), tr("We failed to save the table :("));
      }
   }

   void MainWindow::saveCurrentTableInNewFile()
   {
      TableEdit* table = getActiveTable();
      if (table == nullptr) {
         return;
      }

      QString filepath = QFileDialog::getSaveFileName(
         this, tr("Save VPX file"), table->getFilepath(), "VPX tables (*.vpx)"
      );

      if (m_editor->saveTable(table->getId(), filepath)) {
         statusBar()->showMessage(tr("Table saved as %1").arg(table->getFilepath()));
      }
      else {
         QMessageBox::critical(this, tr("Error"), tr("We failed to save the table :("));
      }
   }

   void MainWindow::openTableMetaDialog()
   {
      TableEdit* table = getActiveTable();
      if (table == nullptr) {
         return;
      }

      TableMetaDialog dialog(table, this);
      dialog.setModal(true);

      dialog.exec();
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
