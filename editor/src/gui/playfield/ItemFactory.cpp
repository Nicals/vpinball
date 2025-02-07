#include <playfield/PlayfieldElement.h>

#include "ItemFactory.h"


namespace vpin::editor {

   ItemFactoryRegister::ItemFactoryRegister(QObject* parent)
      : QObject{parent}
   {
   }

   void ItemFactoryRegister::registerFactory(ItemFactory* factory)
   {
      m_factories.append(factory);
      factory->setParent(this);
   }

   PlayfieldGraphicsObject* ItemFactoryRegister::createGraphicsObject(PlayfieldElement* element) const
   {
      for (auto factory: m_factories) {
         PlayfieldGraphicsObject* object = factory->createGraphicsObject(element);

         if (object != nullptr) {
            return object;
         }
      }

      return nullptr;
   }

}
