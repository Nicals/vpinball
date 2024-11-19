#pragma once

#include <QMutex>
#include <Log.h>


namespace vpin::editor {

   /**
    * A bridge between plog library and Qt logging system.
    */
   class PlogBridge
      : public plog::IAppender
   {
      public:
         void write(const plog::Record& record) override;

      private:
         QMutex m_mutex;
   };

   void configureLogger();

}
