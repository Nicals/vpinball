#include <QDebug>
#include "../PlayfieldElement.h"
#include "../../TableEdit.h"

#include "SetElementPositionCommand.h"


namespace vpin::editor {

   SetElementPositionCommand::SetElementPositionCommand(TableEdit* table, QString elementName, QPointF position)
      : m_table{table},
        m_elementName{elementName},
        m_position{position}
   {
      PlayfieldElement* element = m_table->getElement(elementName);
      m_initialPosition = element->getPosition();

      setText(QString("Move element '%1'").arg(elementName));
   }

   void SetElementPositionCommand::redo()
   {
      PlayfieldElement* element = m_table->getElement(m_elementName);
      element->setPosition(m_position);
   }

   void SetElementPositionCommand::undo()
   {
      PlayfieldElement* element = m_table->getElement(m_elementName);
      element->setPosition(m_initialPosition);
   }

}
