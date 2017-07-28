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

   static char sBuffer[200];
   vsnprintf(sBuffer, 200, format, arguments);

   if (instance && loggingEnabled && shouldLog(DEBUG_FINEST))
   {
      instance->log(DEBUG_FINEST, String(sBuffer));
   }

   va_end(arguments);
}

void Logger::logDebug(
   const char* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   static char sBuffer[200];
   vsnprintf(sBuffer, 200, format, arguments);

   if (instance && loggingEnabled && shouldLog(DEBUG))
   {
      instance->log(DEBUG, String(sBuffer));
   }

   va_end(arguments);
}

void Logger::logInfo(
   const char* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   static char sBuffer[200];
   vsnprintf(sBuffer, 200, format, arguments);

   if (instance && loggingEnabled)
   {
      instance->log(INFO, String(sBuffer));
   }

   va_end(arguments);
}

void Logger::logWarning(
   const char* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   static char sBuffer[200];
   vsnprintf(sBuffer, 200, format, arguments);

   if (instance && loggingEnabled && shouldLog(WARNING))
   {
      instance->log(WARNING, String(sBuffer));
   }

   va_end(arguments);
}

void Logger::logSevere(
   const char* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   static char sBuffer[200];
   vsnprintf(sBuffer, 200, format, arguments);

   if (instance && loggingEnabled && shouldLog(SEVERE))
   {
      instance->log(SEVERE, String(sBuffer));
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

   static char sBuffer[200];
   vsnprintf_P(sBuffer, 200, (PGM_P)format, arguments);

   if (instance && loggingEnabled && shouldLog(DEBUG_FINEST))
   {
      instance->log(DEBUG_FINEST, String(sBuffer));
   }

   va_end(arguments);
}

void Logger::logDebug(
   const __FlashStringHelper* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   static char sBuffer[200];
   vsnprintf_P(sBuffer, 200, (PGM_P)format, arguments);

   if (instance && loggingEnabled && shouldLog(DEBUG))
   {
      instance->log(DEBUG, String(sBuffer));
   }

   va_end(arguments);
}

void Logger::logInfo(
   const __FlashStringHelper* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   static char sBuffer[200];
   vsnprintf_P(sBuffer, 200, (PGM_P)format, arguments);

   if (instance && loggingEnabled && shouldLog(INFO))
   {
      instance->log(INFO, String(sBuffer));
   }

   va_end(arguments);
}

void Logger::logWarning(
   const __FlashStringHelper* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   static char sBuffer[200];
   vsnprintf_P(sBuffer, 200, (PGM_P)format, arguments);

   if (instance && loggingEnabled && shouldLog(WARNING))
   {
      instance->log(WARNING, String(sBuffer));
   }

   va_end(arguments);
}

void Logger::logSevere(
   const __FlashStringHelper* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   static char sBuffer[200];
   vsnprintf_P(sBuffer, 200, (PGM_P)format, arguments);

   if (instance && loggingEnabled && shouldLog(SEVERE))
   {
      instance->log(SEVERE, String(sBuffer));
   }

   va_end(arguments);
}
#endif
