#pragma once

#include <QGraphicsObject>


namespace vpin::editor {

   class PlayfieldElement;

   class PlayfieldGraphicsObject
      : public QGraphicsObject
   {
      public:
         explicit PlayfieldGraphicsObject(PlayfieldElement* element);
         virtual ~PlayfieldGraphicsObject() {};

         PlayfieldElement* getElement() const;

      private:
         PlayfieldElement *m_element;
   };

}
