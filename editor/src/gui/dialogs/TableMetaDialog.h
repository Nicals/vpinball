#pragma once

#include <QDialog>
#include <QLineEdit>


namespace vpin::editor {

   class TableEdit;

   class TableMetaDialog final
      : public QDialog
   {
      Q_OBJECT;

      public:
         TableMetaDialog(TableEdit* table, QWidget* parent = nullptr);

      protected slots:
         void accept() override;

      private:
         TableEdit* m_table;

         QWidget* createGeneralForm();
         QWidget* createRuleForm();

         QLineEdit* m_tableName;
   };

}
