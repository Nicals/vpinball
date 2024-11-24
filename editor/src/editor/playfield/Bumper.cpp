#include "Bumper.h"


namespace vpin::editor {

   Bumper::Bumper(vpin::adapter::Bumper* bumper, QObject* parent)
      : m_bumper{bumper},
        PlayfieldElement{parent}
   {
   }

}
