#include <QLoggingCategory>
#include <QMutex>

#include <utils/Logger.h>

#include "PlogBridge.h"
#include "Appenders/IAppender.h"
#include "Severity.h"


Q_LOGGING_CATEGORY(VPinballCategory, "vpinball");

// Copy-pasted from qloggingcategory.h and added plog::Record.
// This is basically a re-implementation of qcDebug Qt macros with
// file::func::line context injected from a plog::Record instance.
#define PLOG_QLOG(category, level, record) \
    for (QLoggingCategoryMacroHolder<level> qt_category((category)()); qt_category; qt_category.control = false) \
        QMessageLogger(record.getFile(), record.getLine(), record.getFunc(), qt_category.name())


namespace vpin::editor {

   /**
    * A bridge between plog library and Qt logging system.
    */
   class QtAppender: public plog::IAppender
   {
      public:
         void write(const plog::Record& record) override
         {
            m_mutex.lock();
            auto message = qUtf8Printable(record.getMessage());

            switch (record.getSeverity()) {
               case plog::debug:
               case plog::none:
               case plog::verbose:
                  PLOG_QLOG(VPinballCategory, QtDebugMsg, record).debug() << message;
                  break;
               case plog::info:
                  PLOG_QLOG(VPinballCategory, QtInfoMsg, record).info() << message;
                  break;
               case plog::warning:
                  PLOG_QLOG(VPinballCategory, QtWarningMsg, record).warning() << message;
                  break;
               case plog::error:
                  PLOG_QLOG(VPinballCategory, QtCriticalMsg, record).critical() << message;
                  break;
               case plog::fatal:
                  // Will terminate the application. This may not be the behavior we want.
                  PLOG_QLOG(VPinballCategory, QtFatalMsg, record).fatal() << message;
                  break;
            }
            m_mutex.unlock();
         }

      private:
         QMutex m_mutex;
   };


   void bridgePlog()
   {
      static bool initialized = false;
      if (initialized) {
         return;
      }

      auto logger = Logger::GetInstance();
      // Initialise plog but DO NOT CALL Logger::SetupLogger. We don't want
      // to have VPinball default log appender.
      logger->Init();

      static QtAppender qtAppender;

      plog::Logger<PLOG_DEFAULT_INSTANCE_ID>::getInstance()->addAppender(&qtAppender);
      plog::Logger<PLOG_DEFAULT_INSTANCE_ID>::getInstance()->setMaxSeverity(plog::info);
      
      initialized = true;
   }
}
