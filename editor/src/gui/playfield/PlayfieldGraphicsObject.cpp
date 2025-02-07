#include "PlayfieldGraphicsObject.h"

#include <playfield/PlayfieldElement.h>


namespace vpin::editor {

   PlayfieldGraphicsObject::PlayfieldGraphicsObject(PlayfieldElement* element)
      : m_element{element}
   {
   }

   PlayfieldElement* PlayfieldGraphicsObject::getElement() const
   {
      return m_element;
   }

}
