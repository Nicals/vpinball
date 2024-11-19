#include <QDialog>
#include <QScreen>

#include "sizes.h"


namespace vpin::editor {

   void sizeLargeDialog(QDialog* dialog)
   {
      QScreen* screen = dialog->screen();

      if (screen == nullptr) {
         qDebug() << "Getting null dialog screen :(";
         return;
      }

      QRect screenGeometry = screen->availableGeometry();
      // I just found those values looking for common dialog dimensions.
      dialog->resize(screenGeometry.width() * 0.6, screenGeometry.height() * 0.4);
      dialog->setMinimumSize(400, 300);
      dialog->setMaximumSize(1000, 800);
   }

}
