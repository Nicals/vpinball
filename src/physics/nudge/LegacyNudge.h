// license:GPLv3+

#pragma once

#include "physics/nudge/NudgeModel.h"


/**
 * Performs keyboard nudge by applying a force directly to the ball. First in
 * the forward direction, then, after a little while, in the opposite direction.
 *
 * No hardware nudging support.
 */
class LegacyNudge final: public NudgeModel
{
   public:
      LegacyNudge(float strength);

      Vertex2D GetScreenNudge() const override;
      Vertex3Ds GetAcceleration() const override;

      void Nudge(float sn, float cs) override;
      void Update(float dtime) override;

   private:
      int m_nudgeTime = 0;
      float m_strength;
      Vertex2D m_nudgeBack;
      Vertex3Ds m_nudgeAcceleration;
};
