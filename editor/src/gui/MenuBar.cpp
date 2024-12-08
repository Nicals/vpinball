#include <Editor.h>

#include "MenuBar.h"


namespace vpin::editor {

   MenuBar::MenuBar(Editor* editor, QWidget* parent)
      : QMenuBar{parent}
   {
      addMenu(buildFileMenu(editor));
      addMenu(buildEditMenu(editor));
      addMenu(buildViewMenu(editor));
   }

   void MenuBar::actionNeedsTable(QAction* action, Editor* editor) const
   {
      action->setDisabled(!editor->hasTableLoaded());
      connect(editor, &Editor::tableCountChanged, action, [action](int tableCount) {
         action->setEnabled(tableCount > 0);
      });
   }

   QMenu* MenuBar::buildFileMenu(Editor* editor)
   {
      QAction* openTableAction = new QAction(tr("&Open table"));
      openTableAction->setShortcut(Qt::CTRL | Qt::Key_O);
      connect(openTableAction, &QAction::triggered, [this]() { emit openTableRequested(); });

      QAction* saveAction = new QAction(tr("&Save"));
      saveAction->setShortcut(Qt::CTRL | Qt::Key_S);
      actionNeedsTable(saveAction, editor);
      connect(saveAction, &QAction::triggered, [this]() { emit saveTableRequested(); });

      QAction* saveAsAction = new QAction(tr("Save as"));
      saveAsAction->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_S);
      actionNeedsTable(saveAsAction, editor);
      connect(saveAsAction, &QAction::triggered, [this]() { emit saveTableAsRequested(); });

      QAction* closeTableAction = new QAction(tr("Save as"));
      closeTableAction->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_S);
      actionNeedsTable(closeTableAction, editor);
      connect(closeTableAction, &QAction::triggered, [this]() { emit saveTableAsRequested(); });

      QAction* quitAction = new QAction(tr("&Quit"));
      quitAction->setShortcut(Qt::CTRL | Qt::Key_Q);
      connect(quitAction, &QAction::triggered, [this]() { emit quitApplicationRequested(); });

      QMenu* menu = new QMenu(tr("&File"));
      menu->addAction(openTableAction);
      menu->addAction(saveAction);
      menu->addAction(saveAsAction);
      menu->addAction(closeTableAction);
      menu->addSeparator();
      menu->addAction(quitAction);

      return menu;
   }

   QMenu* MenuBar::buildEditMenu(Editor* editor)
   {
      QAction* tableMetaAction = new QAction(tr("Table meta"));
      actionNeedsTable(tableMetaAction, editor);
      connect(tableMetaAction, &QAction::triggered, [this]() { emit editTableMetaRequested(); });

      QAction* settingsAction = new QAction(tr("Settings"));
      connect(settingsAction, &QAction::triggered, [this]() { emit editAppSettingsRequested(); });

      QAction* undoAction = new QAction(tr("Undo"));
      undoAction->setShortcut(Qt::CTRL | Qt::Key_Z);
      actionNeedsTable(undoAction, editor);
      connect(undoAction, &QAction::triggered, [this] { emit undoRequested(); });

      QAction* redoAction = new QAction(tr("Redo"));
      redoAction->setShortcut(Qt::CTRL | Qt::Key_Y);
      actionNeedsTable(redoAction, editor);
      connect(redoAction, &QAction::triggered, [this] { emit redoRequested(); });

      QMenu* menu = new QMenu(tr("&Edit"));
      menu->addAction(undoAction);
      menu->addAction(redoAction);
      menu->addSeparator();
      menu->addAction(tableMetaAction);
      menu->addSeparator();
      menu->addAction(settingsAction);

      return menu;
   }

   QMenu* MenuBar::buildViewMenu(Editor* editor)
   {
      QAction* showUndoStackAction = new QAction(tr("Undo stack"));
      actionNeedsTable(showUndoStackAction, editor);
      showUndoStackAction->setCheckable(true);
      connect(showUndoStackAction, &QAction::triggered, [this](bool checked) { emit showUndoStackRequested(checked); });

      QMenu* menu = new QMenu(tr("&View"));
      menu->addAction(showUndoStackAction);

      return menu;
   }

}
