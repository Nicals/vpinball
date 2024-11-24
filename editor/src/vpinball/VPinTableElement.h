#pragma once

#include <adapter/TableElement.h>


class IEditable;

namespace vpin::adapter
{

   class VPinTableElement
      : public virtual TableElement
   {
      public:
         VPinTableElement(IEditable* editable);
         VPinTableElement(const VPinTableElement&) = delete;

         std::string getName() override;
         void setName(const std::string& name) override;

      private:
         IEditable* m_editable;
   };

}
