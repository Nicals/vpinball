#include <adapter/Bumper.h>

#include "Bumper.h"


namespace vpin::editor {

   Bumper::Bumper(vpin::adapter::Bumper* bumper, QObject* parent)
      : m_bumper{bumper},
        PlayfieldElement{parent}
   {
   }

   QPointF Bumper::getPosition() const
   {
      auto pos = m_bumper->getPosition();
      return QPointF{pos.x, pos.y};
   }

}
