#include <QFileDialog>

#include "PathEdit.h"


namespace vpin::editor {

   PathEdit::PathEdit(QWidget *parent)
      : QLineEdit{parent}
   {
      setup();
   }

   PathEdit::PathEdit(const QString& contents, QWidget *parent)
      : QLineEdit{contents, parent}
   {
      setup();
   }

   void PathEdit::setup()
   {
      QIcon icon(":/icons/regular/folder-open.svg");
      QAction* action = addAction(icon, QLineEdit::TrailingPosition);

      connect(action, &QAction::triggered, this, &PathEdit::openFilePicker);
   }

   void PathEdit::openFilePicker()
   {
      QString filename = QFileDialog::getOpenFileName(this, tr("Open File"));

      if (filename.isEmpty()) {
         return;
      }

      setText(filename);
      setModified(true);
   }

}
