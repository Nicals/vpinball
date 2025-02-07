#include <QApplication>
#include <QtConcurrent>
#include <QCoreApplication>
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QUndoStack>
#include <QUndoGroup>
#include <QUndoView>

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

      // Dock windows
      m_undoDock = new QDockWidget{tr("Undo stack")};
      m_undoDock->setWidget(new QUndoView{m_editor->getUndoGroup()});

      // Main Menu
      connect(menu, &MenuBar::openTableRequested, this, &MainWindow::loadTable);
      connect(menu, &MenuBar::saveTableRequested, this, &MainWindow::saveCurrentTable);
      connect(menu, &MenuBar::saveTableAsRequested, this, &MainWindow::saveCurrentTableInNewFile);
      connect(menu, &MenuBar::closeTableRequested, this, &MainWindow::closeActiveTable);
      connect(menu, &MenuBar::quitApplicationRequested, this, &MainWindow::quitApplication, Qt::QueuedConnection);
      connect(menu, &MenuBar::editTableMetaRequested, this, &MainWindow::openTableMetaDialog);
      connect(menu, &MenuBar::editAppSettingsRequested, this, &MainWindow::openSettingsDialog);
      connect(menu, &MenuBar::showUndoStackRequested, this, &MainWindow::showUndoDock);
   }

   void MainWindow::loadTable()
   {
      QString filepath = QFileDialog::getOpenFileName(
         this, tr("Open VPX file"), QString(), "VPX tables (*.vpx)"
      );

      if (filepath.isEmpty()) {
         return;
      }

      setDisabled(true);
      statusBar()->showMessage(tr("Loading table: %1").arg(filepath));

      QFuture<bool> future = QtConcurrent::run([this, filepath] {
         return m_editor->loadTable(filepath);
      });

      QFutureWatcher<bool>* watcher = new QFutureWatcher<bool>;
      connect(watcher, &QFutureWatcher<bool>::finished, [this, filepath, watcher]() {
         bool successful = watcher->future().result();

         if (successful) {
            statusBar()->showMessage(tr("Loaded table: %1").arg(filepath), tempMessageTimeout);
         }
         else {
            QMessageBox::critical(this, tr("Error"), tr("Failed to load vpx table %1").arg(filepath));
            statusBar()->showMessage(tr("Failed to load table: %1").arg(filepath), tempMessageTimeout);
         }
         setDisabled(false);
         watcher->deleteLater();
      });

      watcher->setFuture(future);
   }

   bool MainWindow::saveCurrentTable()
   {
      TableEdit* table = m_editor->getActiveTable();
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
      TableEdit* table = m_editor->getActiveTable();
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
      TableEdit* table = m_editor->getActiveTable();
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
      TableEdit* table = m_editor->getActiveTable();
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

   void MainWindow::showUndoDock(bool show)
   {
      if (show) {
         addDockWidget(Qt::LeftDockWidgetArea, m_undoDock);
      } else {
         removeDockWidget(m_undoDock);
      }
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
