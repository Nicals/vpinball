// #include <type_traits>
#include <typeinfo>

#include <core/stdafx.h>
#include <core/main.h>
#include <core/iselect.h>
#include <parts/bumper.h>
#include <utils/Logger.h>

#include <adapter/Table.h>

#include "VPinBumper.h"
#include "VPinTable.h"


namespace vpin::adapter {

   template<typename VPinItem, typename BaseItem, typename ConcreteItem>
   requires std::is_base_of_v<ISelect, VPinItem>
      && std::is_base_of_v<BaseItem, ConcreteItem>
   void insertVPinballItem(std::vector<BaseItem*>& container, ISelect *select)
   {
      VPinItem* item = dynamic_cast<VPinItem*>(select);
      if (item == nullptr) {
         PLOGE << "Failed to convert ISelect item to " << typeid(VPinItem).name() << ". Skipping.";
         return;
      }
      container.push_back(new ConcreteItem(item));
   }

   VPinTable::VPinTable(PinTable* table)
      : m_table{table}
   {
      for (auto editable: table->m_vedit) {
         ISelect* select = editable->GetISelect();
         if (select == nullptr) {
            PLOGE << "Table contains invalid ISelect item. Skipping.";
            continue;
         }

         switch (select->GetItemType()) {
            case eItemSurface:
               PLOGW << "Surface items are not implemented yet";
               break;
            case eItemFlipper:
               PLOGW << "Flipper items are not implemented yet";
               break;
            case eItemTimer:
               PLOGW << "Timer items are not implemented yet";
               break;
            case eItemPlunger:
               PLOGW << "Plunger items are not implemented yet";
               break;
            case eItemTextbox:
               PLOGW << "Textbox items are not implemented yet";
               break;
            case eItemBumper:
               insertVPinballItem<::Bumper, Bumper, VPinBumper>(m_bumpers, select);
               break;
            case eItemTrigger:
               PLOGW << "Trigger items are not implemented yet";
               break;
            case eItemLight:
               PLOGW << "Light items are not implemented yet";
               break;
            case eItemKicker:
               PLOGW << "Kicker items are not implemented yet";
               break;
            case eItemDecal:
               PLOGW << "Decal items are not implemented yet";
               break;
            case eItemGate:
               PLOGW << "Gate items are not implemented yet";
               break;
            case eItemSpinner:
               PLOGW << "Spinner items are not implemented yet";
               break;
            case eItemRamp:
               PLOGW << "Ramp items are not implemented yet";
               break;
            case eItemTable:
               PLOGW << "Table items are not implemented yet";
               break;
            case eItemLightCenter:
               PLOGW << "LightCenter items are not implemented yet";
               break;
            case eItemDragPoint:
               PLOGW << "DragPoint items are not implemented yet";
               break;
            case eItemCollection:
               PLOGW << "Collection items are not implemented yet";
               break;
            case eItemDispReel:
               PLOGW << "DispReel items are not implemented yet";
               break;
            case eItemLightSeq:
               PLOGW << "LightSeq items are not implemented yet";
               break;
            case eItemPrimitive:
               PLOGW << "Primitive items are not implemented yet";
               break;
            case eItemFlasher:
               PLOGW << "Flasher items are not implemented yet";
               break;
            case eItemRubber:
               PLOGW << "Rubber items are not implemented yet";
               break;
            case eItemHitTarget:
               PLOGW << "HitTarget items are not implemented yet";
               break;
            case eItemBall:
               PLOGW << "Ball items are not implemented yet";
               break;
            case eItemTypeCount:
               PLOGE << "Invalid item type eItemTypeCount has been encountered. Ignoring.";
               break;
            case eItemInvalid:
               PLOGE << "Invalid item type eItemInvalid has been encountered. Ignoring.";
               break;
            default:
               PLOGE << "Unknown item type encountered: " << select->GetItemType();
               break;
         }
      }
   }

   std::string VPinTable::getName() const
   {
      return m_table->m_szTableName;
   }

   void VPinTable::setName(const std::string& name)
   {
      m_table->m_szTableName = name;
   }
}
