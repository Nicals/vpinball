#pragma once

#include <QPointF>
#include <QUndoCommand>


namespace vpin::editor {

   class TableEdit;

   class SetElementPositionCommand
      : public QUndoCommand
   {
      public:
         SetElementPositionCommand(TableEdit* table, QString elementName, QPointF position);

         void redo() override;
         void undo() override;

      private:
         TableEdit* m_table;
         QString m_elementName;
         QPointF m_position;
         QPointF m_initialPosition;
   };

}
