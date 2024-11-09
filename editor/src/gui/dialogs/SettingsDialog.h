#pragma once

#include <QDialog>
#include <QLineEdit>


namespace vpin::editor {

   class SettingsDialog final
      : public QDialog
   {
      Q_OBJECT

      public:
         SettingsDialog(QWidget *parent = nullptr);

         void saveAndClose();

      private:
         QLineEdit* m_vpinballExecutablePath;
   };

}
