#pragma once

#include <QLineEdit>


namespace vpin::editor {

   /**
    * A LineEdit with a file selection addon.
    */
   class PathEdit final
      : public QLineEdit
   {
      Q_OBJECT

      public:
         PathEdit(QWidget *parent = nullptr);
         PathEdit(const QString& contents, QWidget *parent = nullptr);

      private:
         void setup();
         void openFilePicker();
   };

}
