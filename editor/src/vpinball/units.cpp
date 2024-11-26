#include <core/main.h>

#include <adapter/units.h>


namespace vpin::adpater {

   float mm_to_vpu(float mm)
   {
      return MMTOVPU(mm);
   }

   float vpu_to_mm(float vpu)
   {
      return VPUTOMM(vpu);
   }

   float inches_to_vpu(float inches)
   {
      return INCHESTOVPU(inches);
   }

   float vpu_to_inches(float vpu)
   {
      return VPUTOINCHES(vpu);
   }

}
