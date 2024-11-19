#include <QDebug>
#include <QTextStream>

#include <qdebug.h>
#include <utils/Logger.h>

#include "PlogBridge.h"


namespace vpin::editor {

   void PlogBridge::write(const plog::Record& record)
   {
      m_mutex.lock();

      tm time;
      plog::util::localtime_s(&time, &record.getTime().time);

      QString message;
      QString level;

      switch (record.getSeverity()) {
         case plog::none:
            level = "none";
            break;
         case plog::verbose:
            level = "verbose";
            break;
         case plog::debug:
            level = "debug";
            break;;
         case plog::info:
            level = "info";
            break;;
         case plog::warning:
            level = "warning";
            break;
         case plog::error:
            level = "critical";
            break;
         case plog::fatal:
            level = "fatal";
            break;
      }

      QTextStream ss(&message);
      ss << "["
         << QString::number(time.tm_hour).rightJustified(2, '0')
         << ":" << QString::number(time.tm_min).rightJustified(2, '0')
         << ":" << QString::number(time.tm_sec).rightJustified(2, '0')
         << "." << QString::number(record.getTime().millitm).rightJustified(3, '0')
         << "] [VPinball] [" << level << "] " << record.getMessage();

      switch (record.getSeverity()) {
         case plog::debug:
         case plog::none:
         case plog::verbose:
            qDebug(qUtf8Printable(message));
            break;
         case plog::info:
            qInfo(qUtf8Printable(message));
            break;
         case plog::warning:
            qWarning(qUtf8Printable(message));
            break;
         case plog::error:
            qCritical(qUtf8Printable(message));
            break;
         case plog::fatal:
            // Will terminate the application. This may not be the behavior we want.
            qFatal(qUtf8Printable(message));
            break;
      }
      m_mutex.unlock();
   }


   void configureLogger()
   {
      static bool initialized = false;
      if (initialized) {
         return;
      }

      auto logger = Logger::GetInstance();
      logger->Init();

      static vpin::editor::PlogBridge qtAppender;

      plog::Logger<PLOG_DEFAULT_INSTANCE_ID>::getInstance()->addAppender(&qtAppender);
      plog::Logger<PLOG_DEFAULT_INSTANCE_ID>::getInstance()->setMaxSeverity(plog::info);
      
      initialized = true;
   }
}
