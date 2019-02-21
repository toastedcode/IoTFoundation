// *****************************************************************************
// *****************************************************************************
// Logger.cpp
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include "Logger.h"

Logger* Logger::instance = 0;

bool Logger::loggingEnabled = true;

LogLevel Logger::logLevel = DEBUG;

char Logger::sBuffer[Logger::BUFFER_SIZE];

bool Logger::recursionGuard = false;

LogLevel fromString(
   const String& logLevelString)
{
   LogLevel logLevel = SEVERE;

   for (int i = LOG_LEVEL_FIRST; i < LOG_LEVEL_LAST; i++)
   {
      if (logLevelString == toString(static_cast<LogLevel>(i)))
      {
         logLevel = static_cast<LogLevel>(i);
         break;
      }
   }

   return (logLevel);
}

void Logger::setLogger(
   Logger* logger)
{
   if (instance != 0)
   {
      delete instance;
   }

   instance = logger;
}

void Logger::setLogLevel(
   const LogLevel& logLevel)
{
   Logger::logLevel = logLevel;
}

LogLevel Logger::getLogLevel()
{
   return (logLevel);
}

void Logger::logDebugFinest(
   const char* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   logAt(DEBUG_FINEST, format, arguments);

   va_end(arguments);
}

void Logger::logDebug(
   const char* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   logAt(DEBUG, format, arguments);

   va_end(arguments);
}

void Logger::logInfo(
   const char* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   logAt(INFO, format, arguments);

   va_end(arguments);
}

void Logger::logWarning(
   const char* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   logAt(WARNING, format, arguments);

   va_end(arguments);
}

void Logger::logSevere(
   const char* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   logAt(SEVERE, format, arguments);

   va_end(arguments);
}

void Logger::logAt(
   const LogLevel& logLevel,
   const char* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   if (instance && loggingEnabled && shouldLog(logLevel) && !recursionGuard)
   {
      recursionGuard = true;

      vsnprintf(sBuffer, BUFFER_SIZE, format, arguments);

      instance->log(logLevel, String(sBuffer));

      recursionGuard = false;
   }

   va_end(arguments);
}

#ifdef ARDUINO
void Logger::logDebugFinest(
   const __FlashStringHelper* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   logAt(DEBUG_FINEST, format, arguments);

   va_end(arguments);
}

void Logger::logDebug(
   const __FlashStringHelper* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   logAt(DEBUG, format, arguments);

   va_end(arguments);
}

void Logger::logInfo(
   const __FlashStringHelper* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   logAt(INFO, format, arguments);

   va_end(arguments);
}

void Logger::logWarning(
   const __FlashStringHelper* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   logAt(WARNING, format, arguments);

   va_end(arguments);
}

void Logger::logSevere(
   const __FlashStringHelper* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   logAt(SEVERE, format, arguments);

   va_end(arguments);
}

void Logger::logAt(
   const LogLevel& logLevel,
   const __FlashStringHelper* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   if (instance && loggingEnabled && shouldLog(logLevel) && !recursionGuard)
   {
      recursionGuard = true;

      vsnprintf_P(sBuffer, BUFFER_SIZE, (PGM_P)format, arguments);

      instance->log(logLevel, String(sBuffer));

      recursionGuard = false;
   }

   va_end(arguments);
}
#endif
