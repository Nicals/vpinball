#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtGlobal>

#include <settings.h>

#include "../widgets/PathEdit.h"
#include "SettingsDialog.h"
#include "sizes.h"


namespace vpin::editor {

   SettingsDialog::SettingsDialog(QWidget* parent)
      : QDialog(parent)
   {
      sizeLargeDialog(this);

      QSettings settings;

      m_vpinballExecutablePath = new PathEdit(settings.value("VPinballPath").toString());

      // Settings form
      QFormLayout* formLayout = new QFormLayout;
      formLayout->addRow(new QLabel("VPinball executable path:"), m_vpinballExecutablePath);

      // Validation buttons
      QPushButton* cancelButton = new QPushButton(tr("Cancel"));
      connect(cancelButton, &QPushButton::clicked, this, &QDialog::close);

      QPushButton* validateButton = new QPushButton(tr("Ok"));
      connect(validateButton, &QPushButton::clicked, this, &SettingsDialog::saveAndClose);

      // Setting up layout
      QHBoxLayout* controlLayout = new QHBoxLayout;
      controlLayout->addStretch();
      controlLayout->addWidget(cancelButton);
      controlLayout->addWidget(validateButton);

      QVBoxLayout* mainLayout = new QVBoxLayout();
      mainLayout->addLayout(formLayout);
      mainLayout->addLayout(controlLayout);

      setLayout(mainLayout);
   }

   void SettingsDialog::saveAndClose()
   {
      QSettings settings;

      settings.setValue(settings::vpinball_executable_path, m_vpinballExecutablePath->text());

      close();
   }
}
