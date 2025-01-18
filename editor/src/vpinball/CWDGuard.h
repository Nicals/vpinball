#pragma once

#include <filesystem>


namespace vpin::adapter
{
   
   /**
    * Saves the current working directory upon construction and restores it when
    * the object goes out of scope, ensuring that any changes to the
    * working directory within a function do not persist unintentionally.
    */
   class CWDGuard final
   {
      public:
         CWDGuard();
         ~CWDGuard();

      private:
         std::filesystem::path m_originalPath;
   };
}
