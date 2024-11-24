#pragma once

#include <adapter/Table.h>


class PinTable;

namespace vpin::adapter
{

   class Bumper;

   class VPinTable final
      : public Table
   {
      public:
         VPinTable(PinTable* table);
         VPinTable(const VPinTable&) = delete;
         virtual ~VPinTable() override {}

         std::string getName() const override;
         void setName(const std::string& name) override;

         const std::vector<Bumper*> getBumpers() const override;

      private:
         PinTable* m_table;

         std::vector<Bumper*> m_bumpers;
   };
}
