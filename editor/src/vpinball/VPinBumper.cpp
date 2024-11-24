#include <core/main.h>
#include <parts/bumper.h>

#include "VPinBumper.h"


namespace vpin::adapter {

   VPinBumper::VPinBumper(::Bumper* bumper)
      : m_bumper{bumper},
        VPinTableElement{bumper}
   {
   }

   const Point2D VPinBumper::getPosition() const
   {
      return {m_bumper->m_d.m_vCenter.x, m_bumper->m_d.m_vCenter.y};
   }

   void VPinBumper::setPosition(const Point2D& point)
   {
      m_bumper->m_d.m_vCenter.Set(point.x, point.y);
   }

}
