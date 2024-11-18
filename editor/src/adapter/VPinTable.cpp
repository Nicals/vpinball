#include "editor/src/adapter/VPinTable.h"
#include <core/stdafx.h>
#include <core/main.h>
#include <utils/Logger.h>

#include <adapter/Table.h>


namespace vpin::editor {

   VPinTable::VPinTable(PinTable* table)
      : m_table{table}
   {
   }

   std::string VPinTable::getName() const
   {
      return m_table->m_szTableName;
   }

   void VPinTable::setName(const std::string& name)
   {
      m_table->m_szTableName = name;
   }
}
