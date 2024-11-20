#include <QTabBar>

#include <Editor.h>
#include <TableEdit.h>

#include "blueprint/TableBlueprint.h"
#include "TableTabs.h"


namespace vpin::editor {

   TableTabs::TableTabs(Editor* editor, QWidget* parent)
      : m_editor{editor},
        QTabWidget{parent}
   {
      connect(m_editor, &Editor::tableLoaded, this, &TableTabs::createNewTableTab);
   }

   void TableTabs::createNewTableTab(const QUuid& tableId)
   {
      TableEdit* table = m_editor->getTable(tableId);

      QWidget* page = new TableBlueprint(table);
      page->setProperty("tableId", tableId);

      int tabIndex = addTab(page, table->getName());
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
   }

}
