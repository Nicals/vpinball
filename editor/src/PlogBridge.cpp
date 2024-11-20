#include <QDebug>

#include <utils/Logger.h>

#include "PlogBridge.h"
#include "Severity.h"


namespace vpin::editor {

   void PlogBridge::write(const plog::Record& record)
   {
      m_mutex.lock();

      QMessageLogger logger(record.getFile(), record.getLine(), record.getFunc(), "VPinball");

      switch (record.getSeverity()) {
         case plog::debug:
         case plog::none:
         case plog::verbose:
            logger.debug() << qUtf8Printable(record.getMessage());
            break;
         case plog::info:
            logger.info() << qUtf8Printable(record.getMessage());
            break;
         case plog::warning:
            logger.warning() << qUtf8Printable(record.getMessage());
            break;
         case plog::error:
            logger.critical() << qUtf8Printable(record.getMessage());
            break;
         case plog::fatal:
            // Will terminate the application. This may not be the behavior we want.
            logger.fatal() << qUtf8Printable(record.getMessage());
            break;
      }
      m_mutex.unlock();
   }


   void bridgePlog(bool verbose)
   {
      plog::Severity maxSeverity = verbose ? plog::info : plog::warning;

      static bool initialized = false;
      if (initialized) {
         return;
      }

      auto logger = Logger::GetInstance();
      logger->Init();

      static vpin::editor::PlogBridge qtAppender;

      plog::Logger<PLOG_DEFAULT_INSTANCE_ID>::getInstance()->addAppender(&qtAppender);
      plog::Logger<PLOG_DEFAULT_INSTANCE_ID>::getInstance()->setMaxSeverity(maxSeverity);
      
      initialized = true;
   }
}
