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

   QGraphicsObject* ItemFactoryRegister::createGraphicsObject(PlayfieldElement* element) const
   {
      for (auto factory: m_factories) {
         QGraphicsObject* object = factory->createGraphicsObject(element);

         if (object != nullptr) {
            return object;
         }
      }

      return nullptr;
   }

}
