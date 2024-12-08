#include <QApplication>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QUndoStack>

#include <Editor.h>
#include <TableEdit.h>

#include "dialogs/SettingsDialog.h"
#include "dialogs/TableMetaDialog.h"
#include "MainWindow.h"
#include "MenuBar.h"
#include "TableTabs.h"

namespace vpin::editor {

   MainWindow::MainWindow(Editor* editor, QWidget* parent)
      : m_editor{editor},
        QMainWindow(parent)
   {
      m_editor->setParent(this);

      // Ensures the status bar is initially visible
      setStatusBar(new QStatusBar);

      // Window content
      m_tabs = new TableTabs{m_editor};
      setCentralWidget(m_tabs);

      // Main menu bar
      MenuBar* menu = new MenuBar{m_editor, this};
      setMenuBar(menu);

      connect(menu, &MenuBar::openTableRequested, this, &MainWindow::loadTable);
      connect(menu, &MenuBar::saveTableRequested, this, &MainWindow::saveCurrentTable);
      connect(menu, &MenuBar::saveTableAsRequested, this, &MainWindow::saveCurrentTableInNewFile);
      connect(menu, &MenuBar::closeTableRequested, this, &MainWindow::closeActiveTable);
      connect(menu, &MenuBar::quitApplicationRequested, this, &MainWindow::quitApplication, Qt::QueuedConnection);
      connect(menu, &MenuBar::editTableMetaRequested, this, &MainWindow::openTableMetaDialog);
      connect(menu, &MenuBar::editAppSettingsRequested, this, &MainWindow::openSettingsDialog);
      connect(menu, &MenuBar::undoRequested, this, &MainWindow::undo);
      connect(menu, &MenuBar::redoRequested, this, &MainWindow::redo);
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
         statusBar()->showMessage(tr("Loaded table: %1").arg(filepath), tempMessageTimeout);
      }
      else
      {
         QMessageBox::critical(this, tr("Error"), tr("Failed to load vpx table %1").arg(filepath));
      }
   }

   bool MainWindow::saveCurrentTable()
   {
      TableEdit* table = getActiveTable();
      if (table == nullptr) {
         return false;
      }

      if (table->getFilepath().isEmpty()) {
         return saveCurrentTableInNewFile();
      }

      if (!m_editor->saveTable(table->getId(), table->getFilepath())) {
         QMessageBox::critical(this, tr("Error"), tr("We failed to save the table :("));
         return false;
      }

      statusBar()->showMessage(tr("Table saved as %1").arg(table->getFilepath()), tempMessageTimeout);

      return true;
   }

   bool MainWindow::saveCurrentTableInNewFile()
   {
      TableEdit* table = getActiveTable();
      if (table == nullptr) {
         return false;
      }

      QString filepath = QFileDialog::getSaveFileName(
         this, tr("Save VPX file"), table->getFilepath(), "VPX tables (*.vpx)"
      );

      if (filepath.isEmpty()) {
         qDebug() << "Aborting saving in new file: empty filepath";
         return false;
      }

      if (!m_editor->saveTable(table->getId(), filepath)) {
         QMessageBox::critical(this, tr("Error"), tr("We failed to save the table :("));
         return false;
      }

      statusBar()->showMessage(tr("Table saved as %1").arg(table->getFilepath()), tempMessageTimeout);

      return true;
   }

   void MainWindow::closeActiveTable()
   {
      TableEdit* table = getActiveTable();
      if (table == nullptr) {
         return;
      }

      if (table->isDirty()) {
         QMessageBox::StandardButton reply;
         reply = QMessageBox::question(
            this,
            tr("Close table"),
            tr("Closing this table will discard unsaved work. Do you want to save it first ?"),
            QMessageBox::Yes | QMessageBox::No
         );

         if (reply == QMessageBox::Yes) {
            if (!saveCurrentTable()) {
               qDebug() << "Closing table has been aborted on save pending changes stage";
               return;
            }

            qDebug() << "Saving current table before closing it.";
         }
         else {
            qInfo() << "Closing table with pending changes.";
         }
      }

      qDebug() << "Table" << table->getName() << "closed";

      statusBar()->showMessage(tr("Table %1 has been closed.").arg(table->getName()), tempMessageTimeout);
      m_editor->closeTable(table->getId());
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

      statusBar()->showMessage(tr("Settings have been saved."), tempMessageTimeout);
   }

   void MainWindow::undo()
   {
      TableEdit* table = getActiveTable();
      if (table == nullptr) {
         return;
      }

      if (!table->getUndoStack()->canUndo()) {
         statusBar()->showMessage(tr("Nothing to undo."), tempMessageTimeout);
      }

      table->getUndoStack()->undo();
   }

   void MainWindow::redo()
   {
      TableEdit* table = getActiveTable();
      if (table == nullptr) {
         return;
      }

      if (!table->getUndoStack()->canRedo()) {
         statusBar()->showMessage(tr("Nothing to redo."), tempMessageTimeout);
      }

      table->getUndoStack()->redo();
   }

   void MainWindow::quitApplication()
   {
      if (m_editor->hasPendingChanges()) {
         QMessageBox::StandardButton reply;
         reply = QMessageBox::warning(
            this,
            tr("Pending changes"),
            tr("Some tables have pending changes. Closing the application will discard any changes. Do you really want to quit now ?"),
            QMessageBox::Yes | QMessageBox::No
         );

         if (reply == QMessageBox::No) {
            return;
         }

         qInfo() << "Closing editor discarding pending changes";
      }

      qApp->quit();
   }
}
