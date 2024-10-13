// license:GPLv3+

#include "physics/nudge/TableAccelerationNudge.h"
#include "math/vector.h"
#include "physics/physconst.h"


TableAccelerationNudge::TableAccelerationNudge(Player* player, const float nudgeTime)
   : m_player{player}
{
   constexpr float dampingRatio = 0.5f;

   m_nudgeSpring = (M_PI * M_PI) / (nudgeTime * nudgeTime * (1.f - dampingRatio * dampingRatio));
   m_nudgeDamping = dampingRatio * 2.0 * sqrtf(m_nudgeSpring);

   m_tableAcceleration.SetZero();
   m_tableVel.SetZero();
   m_tableDisplacement.SetZero();
}

Vertex2D TableAccelerationNudge::GetScreenNudge() const
{
   return {m_tableDisplacement.x, -m_tableDisplacement.y};
}

Vertex3Ds TableAccelerationNudge::GetAcceleration() const
{
   return m_tableAcceleration;
}

void TableAccelerationNudge::Nudge(float sn, float cs)
{
   m_tableVel.x += sn;
   m_tableVel.y -= cs;
}

void TableAccelerationNudge::Update(float dtime)
{
   const Vertex3Ds tableVelOld = m_tableVel;

   // Perform keyboard nudge by simulating table movement modeled as a mass-spring-damper system
   //   u'' = -k u - c u'
   // with a spring constant k and a damping coefficient c
   const Vertex3Ds force = -m_nudgeSpring * m_tableDisplacement - m_nudgeDamping * m_tableVel;
   m_tableVel += (float)PHYS_FACTOR * force;
   m_tableDisplacement += (float)PHYS_FACTOR * m_tableVel;

   m_tableAcceleration = (m_tableVel - tableVelOld) / (float)PHYS_FACTOR;

   // Acquire from sensor input
   Vertex2D sensor = m_player->GetRawAccelerometer();

   // Simulate hardware nudge by getting the cabinet velocity and applying it to the table spring model
   if (m_player->IsAccelInputAsVelocity())
   {
      // Compute acceleration from acquired table velocity and apply it as a force to the balls.
      // Apply the external accelerometer-based nudge velocity input (which is
      // a separate input from the traditional acceleration input)
      Vertex3Ds sensorTableVelocity(sensor.x, sensor.y, 0.f);
      m_tableAcceleration += (sensorTableVelocity - m_prevSensorTableVelocity) / (float)PHYS_FACTOR;
      m_prevSensorTableVelocity = sensorTableVelocity;

      m_nudgeAcceleration.SetZero();
   }
   else
   {
      // Simulate hardware nudge by getting the cabinet acceleration and applying it directly to the ball
      m_nudgeAcceleration.Set(sensor.x, sensor.y, 0.f);
   }
}
