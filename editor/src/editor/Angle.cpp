#include <QtMath>

#include <qmath.h>

#include "Angle.h"


namespace vpin::editor {

   Angle::Angle(): m_degrees{0.0}
   {
   }

   Angle::Angle(float degrees): m_degrees{degrees}
   {
   }

   Angle Angle::fromDegrees(float degrees)
   {
      return Angle{degrees};
   }

   Angle Angle::fromRadians(float radians)
   {
      return Angle{qRadiansToDegrees(radians)};
   }

   float Angle::degrees() const
   {
      return m_degrees;
   }

   float Angle::radians() const
   {
      return qRadiansToDegrees(m_degrees);
   }

   bool Angle::operator==(const Angle& other) const
   {
      return qFuzzyCompare(m_degrees, other.m_degrees);
   }

   bool Angle::operator!=(const Angle& other) const
   {
      return !qFuzzyCompare(m_degrees, other.m_degrees);
   }

}
