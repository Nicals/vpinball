#pragma once


namespace vpin::editor {

   /**
    * Quick and dirty utility class for angles.
    *
    * The *current* goal is only to make sure that devs alway explicitly knows
    * which angle unit they are working with.
    *
    * We might need/want to add functionalities on this class such as
    * arithmetics or normalization. At the time of writing this, I don't need
    * such features.
    */
   class Angle
   {
      public:
         Angle();

         static Angle fromDegrees(float degrees);
         static Angle fromRadians(float radians);

         float degrees() const;
         float radians() const;

         bool operator==(const Angle& other) const;
         bool operator!=(const Angle& other) const;

      private:
         explicit Angle(float degrees);

         float m_degrees;
   };

}
