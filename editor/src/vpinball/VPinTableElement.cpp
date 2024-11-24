#include <core/main.h>
#include <core/ieditable.h>

#include "VPinTableElement.h"


namespace vpin::adapter {

   VPinTableElement::VPinTableElement(IEditable* editable)
      : m_editable{editable}
   {
   }

   void VPinTableElement::setName(const std::string& name)
   {
      m_editable->SetName(name);
   }

   std::string VPinTableElement::getName()
   {
      return std::string(m_editable->GetName());
   }

}
