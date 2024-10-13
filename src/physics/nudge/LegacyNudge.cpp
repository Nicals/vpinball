// license:GPLv3+

#include "physics/nudge/LegacyNudge.h"


LegacyNudge::LegacyNudge(float strength)
   : m_strength{strength}
{
   m_nudgeBack = Vertex2D(0.f, 0.f);
   m_nudgeAcceleration.SetZero();
}

Vertex2D LegacyNudge::GetScreenNudge() const
{
   return {
      m_nudgeBack.x * sqrf((float)m_nudgeTime * 0.01f),
      -m_nudgeBack.y * sqrf((float)m_nudgeTime * 0.01f),
   };
}

Vertex3Ds LegacyNudge::GetAcceleration() const
{
   return m_nudgeAcceleration;
}

void LegacyNudge::Nudge(float sn, float cs)
{
   m_nudgeBack.x = sn * m_strength;
   m_nudgeBack.y = -cs * m_strength;
   m_nudgeTime = 100;
}

void LegacyNudge::Update(float dtime)
{
   m_nudgeTime--;

   if (m_nudgeTime == 95) {
      m_nudgeAcceleration.x = -m_nudgeBack.x * 2.f;
      m_nudgeAcceleration.y = m_nudgeBack.y * 2.f;
   }
   else if (m_nudgeTime == 90)
   {
      m_nudgeAcceleration.x = m_nudgeBack.x;
      m_nudgeAcceleration.y = m_nudgeBack.y;
   }
   else
   {
      m_nudgeAcceleration.SetZero();
   }
}
