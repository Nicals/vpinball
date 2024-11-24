#include "PlayfieldElement.h"


namespace vpin::editor {

   PlayfieldElement::PlayfieldElement(QObject* parent)
      : QObject{parent}
   {
   }

   void PlayfieldElement::setName(const QString& name)
   {
      m_name = name;
      emit changed();
   }

   const QString& PlayfieldElement::getName() const
   {
      return m_name;
   }

}
