#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QSplitter>
#include <QStackedWidget>
#include <QVBoxLayout>

#include <TableEdit.h>

#include "TableMetaDialog.h"
#include "sizes.h"


namespace vpin::editor {

   TableMetaDialog::TableMetaDialog(TableEdit* table, QWidget* parent)
      : m_table{table},
        QDialog{parent}
   {
      setWindowTitle(tr("Table metadata: %1").arg(m_table->getName()));
      sizeLargeDialog(this);

      QStackedWidget* stack = new QStackedWidget(this);
      stack->addWidget(createGeneralForm());
      stack->addWidget(createRuleForm());

      QListWidget* sections = new QListWidget(this);
      sections->addItem(tr("General"));
      sections->addItem(tr("Rules"));

      connect(sections, &QListWidget::currentRowChanged, stack, &QStackedWidget::setCurrentIndex);
      sections->setCurrentRow(0);

      QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
      splitter->addWidget(sections);
      splitter->addWidget(stack);

      QDialogButtonBox* buttons = new QDialogButtonBox(this);
      buttons->addButton(QString(tr("Cancel")), QDialogButtonBox::RejectRole);
      connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
      buttons->addButton(QString(tr("Save")), QDialogButtonBox::AcceptRole);
      connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);

      QVBoxLayout* layout = new QVBoxLayout(this);
      layout->addWidget(splitter);
      layout->addWidget(buttons);

      setLayout(layout);
   }

   QWidget* TableMetaDialog::createGeneralForm()
   {
      m_tableName = new QLineEdit;
      m_tableName->setText(m_table->getName());
      m_tableName->setPlaceholderText(tr("name"));
      m_tableName->setMaxLength(200);

      QFormLayout* layout = new QFormLayout;
      layout->addRow(tr("Name"), m_tableName);

      QWidget* form = new QWidget;
      form->setLayout(layout);

      return form;
   }

   QWidget* TableMetaDialog::createRuleForm()
   {
      return new QLabel("Rules (TBD)");
   }

   void TableMetaDialog::accept()
   {
      m_table->setName(m_tableName->text());

      QDialog::accept();
   }

}
