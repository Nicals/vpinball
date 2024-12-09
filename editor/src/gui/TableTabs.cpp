#include <QTabBar>

#include <Editor.h>
#include <TableEdit.h>

#include "playfield/Playfield.h"
#include "TableTabs.h"


namespace vpin::editor {

   TableTabs::TableTabs(Editor* editor, QWidget* parent)
      : m_editor{editor},
        QTabWidget{parent}
   {
      tabBar()->setIconSize(QSize(8, 8));

      connect(m_editor, &Editor::activeTableChanged, this, &TableTabs::setCurrentTableTab);
      connect(this, &QTabWidget::currentChanged, this, &TableTabs::activateTabTable);
   }

   int TableTabs::findTableWidget(const QUuid& id) const
   {
      for (int index=0 ; index < count() ; index++) {
         QVariant tableId = widget(index)->property("tableId");
         if (!tableId.isValid()) {
            continue;
         }

         if (tableId.value<QUuid>() == id) {
            return index;
         }
      }

      return -1;
   }

   int TableTabs::createNewTableTab(TableEdit* table)
   {
      QWidget* page = new Playfield(m_editor->getPlayfieldTheme(), table);
      page->setProperty("tableId", table->getId());

      int tabIndex = addTab(page, table->getName());
      setTabIcon(tabIndex, table->isDirty() ? QIcon(":/icons/solid/asterisk.svg") : QIcon());
      setTabToolTip(tabIndex, table->getName());

      // Update tab title when tab name has changed
      connect(table, &TableEdit::nameChanged, [this, page](const QString& tableName) {
         int tabIndex = indexOf(page);
         if (tabIndex == -1) {
            qWarning() << "Received TableEdit::nameChanged event with no associated tab";
            return;
         }

         setTabText(tabIndex, tableName);
         setTabToolTip(tabIndex, tableName);
      });

      // Add icon when table has dirty state
      connect(table, &TableEdit::dirtyStateChanged, [this, page](bool isDirty) {
         int tabIndex = indexOf(page);
         if (tabIndex == -1 ) {
            qWarning() << "Received TableEdit::dirtyStateChange event with no associated tab";
            return;
         }

         setTabIcon(tabIndex, isDirty ? QIcon(":/icons/solid/asterisk.svg") : QIcon());
      });

      // Remove tab when table is about to be closed
      connect(table, &TableEdit::aboutToClose, [this, page]() {
         int tabIndex = indexOf(page);
         if (tabIndex == -1) {
            qWarning() << "Received TableEdit::aboutToClose event with no associated tab";
         }

         removeTab(tabIndex);
      });

      return tabIndex;
   }

   void TableTabs::activateTabTable(int index) const
   {
      if (index == -1) {
         return;
      }

      QWidget* tab = widget(index);
      if (tab == nullptr) {
         qCritical() << "Cannot activate table: invalid tab index" << index;
         return;
      }

      QVariant tableId = tab->property("tableId");
      if (!tableId.isValid()) {
         qCritical() << "Cannot activate table: tab does not have 'tableId' property.";
         return;
      }

      m_editor->setActiveTable(tableId.value<QUuid>());
   }

   void TableTabs::setCurrentTableTab(const QUuid& tableId)
   {
      // Null id would imply that we don't have any more tabs opened.
      if (tableId.isNull()) {
         if (count() != 0) {
            qWarning() << "Active table None received while having" << count() << "tabs.";
         }
         return;
      }

      int tabIndex = findTableWidget(tableId);

      if (tabIndex == -1) {
         tabIndex = createNewTableTab(m_editor->getActiveTable());
      }

      setCurrentIndex(tabIndex);
   }

}
