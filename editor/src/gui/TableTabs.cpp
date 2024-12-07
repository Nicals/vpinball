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

      connect(m_editor, &Editor::tableLoaded, this, &TableTabs::createNewTableTab);
   }

   void TableTabs::createNewTableTab(const QUuid& tableId)
   {
      TableEdit* table = m_editor->getTable(tableId);

      QWidget* page = new Playfield(m_editor->getPlayfieldTheme(), table);
      page->setProperty("tableId", tableId);

      int tabIndex = addTab(page, table->getName());
      setTabIcon(tabIndex, table->isDirty() ? QIcon(":/icons/solid/asterisk.svg") : QIcon());
      setTabToolTip(tabIndex, table->getName());

      connect(table, &TableEdit::nameChanged, [this, page](const QString& tableName) {
         int tabIndex = indexOf(page);
         if (tabIndex == -1) {
            qWarning() << "Received TableEdit::nameChanged event with no associated tab";
            return;
         }

         setTabText(tabIndex, tableName);
         setTabToolTip(tabIndex, tableName);
      });

      connect(table, &TableEdit::dirtyStateChanged, [this, page](bool isDirty) {
         int tabIndex = indexOf(page);
         if (tabIndex == -1 ) {
            qWarning() << "Received TableEdit::dirtyStateChange event with no associated tab";
            return;
         }

         setTabIcon(tabIndex, isDirty ? QIcon(":/icons/solid/asterisk.svg") : QIcon());
      });

      connect(table, &TableEdit::aboutToClose, [this, page]() {
         int tabIndex = indexOf(page);
         if (tabIndex == -1) {
            qWarning() << "Received TableEdit::aboutToClose event with no associated tab";
         }

         removeTab(tabIndex);
      });
   }

}
