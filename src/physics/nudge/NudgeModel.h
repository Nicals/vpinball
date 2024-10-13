// license:GPLv3+

#pragma once

#include "core/stdafx.h"


/**
 * Interface for nudge model implementation
 */
class NudgeModel
{
   public:
      // Table displacement when nudging
      virtual Vertex2D GetScreenNudge() const = 0;
      virtual Vertex3Ds GetAcceleration() const = 0;

      virtual void Nudge(float sn, float cs) = 0;
      virtual void Update(float dtime) = 0;
};
