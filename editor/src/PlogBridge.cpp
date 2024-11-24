#include <QLoggingCategory>
#include <QMutex>

#include <utils/Logger.h>

#include "PlogBridge.h"
#include "Appenders/IAppender.h"
#include "Severity.h"


Q_LOGGING_CATEGORY(VAdapterCategory, "adapter");
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
            QLoggingCategory category{QString{record.getFunc()}.startsWith("vpin::adapter::") ? "adapter" : "vpinball"};

            switch (record.getSeverity()) {
               case plog::debug:
               case plog::none:
               case plog::verbose:
                  PLOG_QLOG(category, QtDebugMsg, record).debug() << qUtf8Printable(record.getMessage());
                  break;
               case plog::info:
                  PLOG_QLOG(category, QtInfoMsg, record).info() << qUtf8Printable(record.getMessage());
                  break;
               case plog::warning:
                  PLOG_QLOG(category, QtWarningMsg, record).warning() << qUtf8Printable(record.getMessage());
                  break;
               case plog::error:
                  PLOG_QLOG(category, QtCriticalMsg, record).critical() << qUtf8Printable(record.getMessage());
                  break;
               case plog::fatal:
                  // Will terminate the application. This may not be the behavior we want.
                  PLOG_QLOG(category, QtFatalMsg, record).fatal() << qUtf8Printable(record.getMessage());
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
