#include "CWDGuard.h"


namespace vpin::adapter
{

   CWDGuard::CWDGuard()
      : m_originalPath{std::filesystem::current_path()}
   {
   }

   CWDGuard::~CWDGuard()
   {
      std::filesystem::current_path(m_originalPath);
   }
}
