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

void Logger::setLogger(
   Logger* logger)
{
   if (instance != 0)
   {
      delete instance;
   }

   instance = logger;
}

void Logger::logDebug(
   const char* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   static char sBuffer[200];
   vsnprintf(sBuffer, 200, format, arguments);

   if (instance && loggingEnabled)
   {
      instance->log(DEBUG, String(sBuffer));
   }

   va_end(arguments);
}

inline void Logger::logInfo(
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

inline void Logger::logWarning(
   const char* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   static char sBuffer[200];
   vsnprintf(sBuffer, 200, format, arguments);

   if (instance && loggingEnabled)
   {
      instance->log(WARNING, String(sBuffer));
   }

   va_end(arguments);
}

inline void Logger::logSevere(
   const char* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   static char sBuffer[200];
   vsnprintf(sBuffer, 200, format, arguments);

   if (instance && loggingEnabled)
   {
      instance->log(SEVERE, String(sBuffer));
   }

   va_end(arguments);
}
