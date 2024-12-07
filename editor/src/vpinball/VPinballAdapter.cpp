#include <filesystem>
#include <stdexcept>

#include <core/main.h>
#include <core/vpinball_h.h>

#include <vpinball/VPinballAdapter.h>

#include "VPinTable.h"


namespace vpin::adapter {

   VPinballAdapter::VPinballAdapter()
   {
      if (g_pvp != nullptr) {
         throw std::runtime_error("Only one instance of VPinballAdapter can be created.");
      }

      m_vpinball = new VPinball();
      g_pvp = m_vpinball;

      EditableRegistry::RegisterEditable<::Ball>();
      EditableRegistry::RegisterEditable<::Bumper>();
      EditableRegistry::RegisterEditable<::Decal>();
      EditableRegistry::RegisterEditable<::DispReel>();
      EditableRegistry::RegisterEditable<::Flasher>();
      EditableRegistry::RegisterEditable<::Flipper>();
      EditableRegistry::RegisterEditable<::Gate>();
      EditableRegistry::RegisterEditable<::Kicker>();
      EditableRegistry::RegisterEditable<::Light>();
      EditableRegistry::RegisterEditable<::LightSeq>();
      EditableRegistry::RegisterEditable<::Plunger>();
      EditableRegistry::RegisterEditable<::Primitive>();
      EditableRegistry::RegisterEditable<::Ramp>();
      EditableRegistry::RegisterEditable<::Rubber>();
      EditableRegistry::RegisterEditable<::Spinner>();
      EditableRegistry::RegisterEditable<::Surface>();
      EditableRegistry::RegisterEditable<::Textbox>();
      EditableRegistry::RegisterEditable<::Timer>();
      EditableRegistry::RegisterEditable<::Trigger>();
      EditableRegistry::RegisterEditable<::HitTarget>();
   }

   VPinballAdapter::~VPinballAdapter()
   {
      delete m_vpinball;
      g_pvp = nullptr;
   }

   void VPinballAdapter::setThreadCount(std::size_t threadCount) {
      if (threadCount < 1) {
         PLOGE << "Refusing to set thread count '" << threadCount << "'. Must be strictly positive.";
         return;
      }

      m_vpinball->SetLogicalNumberOfProcessors(threadCount);
   }

   Table* VPinballAdapter::loadTable(const std::string& filepath)
   {
      if (!m_tables.empty()) {
         throw std::runtime_error("Loading multiple table is sadly not yet implemented :(");
      }

      // VPinball changes the current working directory to load files.
      // We don't want this.
      std::filesystem::path cwd = std::filesystem::current_path();
      m_vpinball->LoadFileName(filepath, false);
      std::filesystem::current_path(cwd);

      VPinTable* table = new VPinTable(m_vpinball->GetActiveTable());
      m_tables.push_back(table);

      return table;
   }

}
