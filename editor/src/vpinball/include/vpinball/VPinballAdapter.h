#pragma once

#include <adapter/Adapter.h>

#include <vector>


class VPinball;


namespace vpin::adapter {

   class VPinballAdapter final
      : public Adapter
   {
      public:
         VPinballAdapter();
         VPinballAdapter(const VPinballAdapter&) = delete;
         ~VPinballAdapter() override;

         void setThreadCount(std::size_t threadCount);

         virtual Table* loadTable(const std::string& filepath) override;

      private:
         VPinball* m_vpinball;

         std::vector<Table*> m_tables;
   };

}
