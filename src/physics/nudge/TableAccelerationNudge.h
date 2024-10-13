// license:GPLv3+

#pragma once

#include "physics/nudge/NudgeModel.h"
#include "core/stdafx.h"


/**
 * Simulate nudges by emulating a pendulum.
 *
 * NOTE: This comment has been copy pasted from refactored code. Not sure if it
 * correctly applies here.
 *
 * Acceleration based nudge
 * 2. Acceleration based nudge:
 *    - Perform keyboard nudge by applying an impulse to a physic model of the cabinet (spring-mass model, see below)
 *    - Acquire cabinet acceleration from sensor and apply it directly to balls
 * 3. Velocity based nudge:
 *    - Perform keyboard nudge by applying an impulse to a physic model of the cabinet (spring-mass model, see below)
 *    - Acquire cabinet velocity from sensor and apply it to the physic model of the cabinet (same spring-mass model as for keyboard nudge)
 */
class TableAccelerationNudge final: public NudgeModel
{
   public:
      TableAccelerationNudge(Player* player, const float nudgeTime);

      Vertex2D GetScreenNudge() const;
      Vertex3Ds GetAcceleration() const;

      void Nudge(float sn, float cs);
      void Update(float dtime) override;

   private:
      Player* m_player;

      Vertex3Ds m_tableAcceleration;
      Vertex3Ds m_tableVel;
      Vertex3Ds m_tableDisplacement;

      // External accelerometer velocity input.  This is for newer
      // pin cab I/O controllers that can integrate acceleration 
      // samples on the device side to compute the instantaneous
      // cabinet velocity, and pass the velocity data to the host.
      //
      // Velocities computed on the device side are applied to the
      // physics model the same way as the velocities computed from
      // the "spring model" for scripted nudge force inputs.
      Vertex3Ds m_prevSensorTableVelocity;

      // filtered nudge acceleration acquired from hardware or resulting of keyboard nudge
      Vertex3Ds m_nudgeAcceleration;

      // time for one half period (one swing and swing back):
      //   T = pi / omega_d,
      // where
      //   omega_d = omega_0 * sqrt(1 - zeta^2)       (damped frequency)
      //   omega_0 = sqrt(k)                          (undamped frequency)
      // Solving for the spring constant k, we get
      float m_nudgeSpring;

      // The formula for the damping ratio is
      //   zeta = c / (2 sqrt(k)).
      // Solving for the damping coefficient c, we get
      float m_nudgeDamping;
};
