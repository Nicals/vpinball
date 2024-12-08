#pragma once

#include <QMenuBar>


class QAction;

namespace vpin::editor {

   class Editor;

   /**
    * Handls the top menu bar
    */
   class MenuBar
      : public QMenuBar
   {
      Q_OBJECT;

      public:
         MenuBar(Editor* editor, QWidget* parent = nullptr);

      private:
         void actionNeedsTable(QAction* action, Editor* editor) const;

         QMenu* buildFileMenu(Editor* editor);
         QMenu* buildEditMenu(Editor* editor);
         QMenu* buildViewMenu(Editor* editor);

      signals:
         void openTableRequested();
         void saveTableRequested();
         void saveTableAsRequested();
         void closeTableRequested();

         void editAppSettingsRequested();

         void undoRequested();
         void redoRequested();
         void editTableMetaRequested();

         void showUndoStackRequested(bool show);

         void quitApplicationRequested();
   };
}
