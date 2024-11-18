#include <core/stdafx.h>
#include <core/main.h>
#include <utils/Logger.h>

#include <adapter/Table.h>


namespace vpin::editor {

   // A POC that I can load a table
   void load_table(const std::string& filepath)
   {
      VPinball pinball;
      pinball.m_logicalNumberOfProcessors = 1;
      g_pvp = &pinball;

      Logger::GetInstance()->Init();
      Logger::GetInstance()->SetupLogger(true);

      EditableRegistry::RegisterEditable<Ball>();
      EditableRegistry::RegisterEditable<Bumper>();
      EditableRegistry::RegisterEditable<Decal>();
      EditableRegistry::RegisterEditable<DispReel>();
      EditableRegistry::RegisterEditable<Flasher>();
      EditableRegistry::RegisterEditable<Flipper>();
      EditableRegistry::RegisterEditable<Gate>();
      EditableRegistry::RegisterEditable<Kicker>();
      EditableRegistry::RegisterEditable<Light>();
      EditableRegistry::RegisterEditable<LightSeq>();
      EditableRegistry::RegisterEditable<Plunger>();
      EditableRegistry::RegisterEditable<Primitive>();
      EditableRegistry::RegisterEditable<Ramp>();
      EditableRegistry::RegisterEditable<Rubber>();
      EditableRegistry::RegisterEditable<Spinner>();
      EditableRegistry::RegisterEditable<Surface>();
      EditableRegistry::RegisterEditable<Textbox>();
      EditableRegistry::RegisterEditable<Timer>();
      EditableRegistry::RegisterEditable<Trigger>();
      EditableRegistry::RegisterEditable<HitTarget>();

      pinball.LoadFileName(filepath, false);
      PinTable* table = pinball.GetActiveTable();
   }
}
