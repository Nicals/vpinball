#pragma once

#include <QMap>
#include <QUuid>
#include <QObject>

class QUndoGroup;

namespace vpin::adapter {
   class Adapter;
}

namespace vpin::editor {

   class TableEdit;
   class PlayfieldTheme;

   class Editor final
      : public QObject
   {
      Q_OBJECT

      public:
         Editor(vpin::adapter::Adapter* adapter);
         ~Editor();

         PlayfieldTheme* getPlayfieldTheme();
         QUndoGroup* getUndoGroup();

         bool loadTable(const QString& filepath);
         bool saveTable(const QUuid& tableId, const QString& filepath);
         void closeTable(const QUuid& tableId);
         unsigned int getTableCount() const;
         bool hasTableLoaded() const;
         TableEdit* getTable(const QUuid& id);
         TableEdit* getActiveTable() const;
         void setActiveTable(const QUuid& id);
         bool hasPendingChanges() const;

      signals:
         void tableClosed();
         void activeTableChanged(const QUuid&);
         void tableCountChanged(int);

      private:
         vpin::adapter::Adapter* m_adapter;

         QUndoGroup* m_undoGroup;
         PlayfieldTheme* m_theme;

         QMap<QUuid, TableEdit*> m_tables;
         QUuid m_activeTable;
   };
}
