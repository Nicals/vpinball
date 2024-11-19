#pragma once

#include <adapter/Table.h>


class PinTable;

namespace vpin::adapter
{

   class VPinTable
      : public Table
   {
      public:
         VPinTable(PinTable* table);
         VPinTable(const VPinTable&) = delete;
         virtual ~VPinTable() override {}

         std::string getName() const override;
         void setName(const std::string& name) override;

      private:
         PinTable* m_table;
   };
}
