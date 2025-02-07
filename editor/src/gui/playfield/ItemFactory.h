#pragma once

#include "PlayfieldGraphicsObject.h"


namespace vpin::editor {

   class PlayfieldElement;

   /**
    * A factory used to create graphics items for playfield elements.
    */
   class ItemFactory
      : public QObject
   {
      public:
         virtual ~ItemFactory() = default;

         /**
          * Creates a PlayfieldGraphicsObject from a table element.
          * Returns nullptr if the element passed as argument is not compatible
          * with the current factory.
          */
         virtual PlayfieldGraphicsObject* createGraphicsObject(PlayfieldElement* element) const = 0;
   };


   /**
    * Holds a collection of factories used to create visual playfield elements.
    */
   class ItemFactoryRegister
      : public QObject
   {
      public:
         ItemFactoryRegister(QObject* parent = nullptr);

         void registerFactory(ItemFactory* factory);

         /**
          * Creates a new graphics object for the given playfield element.
          * Will return nullptr if no appropriate factory has been registered
          * for the current element.
          */
         PlayfieldGraphicsObject* createGraphicsObject(PlayfieldElement* element) const;

      private:
         QList<ItemFactory*> m_factories;
   };

}
