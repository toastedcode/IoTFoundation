// *****************************************************************************
// *****************************************************************************
// Logger.h
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <stdarg.h>

#include "CommonDefs.hpp"

class Logger
{

public:

   Logger();

   virtual ~Logger();

   static void setLogger(
      Logger* logger);

   static void logDebug(
      const String& string);

   static void logDebug(
      const char* format,
      ...);

   static void setEnabled(
      const bool& loggingEnabled);

   virtual void log(
      const String& string);

protected:

   static Logger* getInstance();

private:

   static Logger* instance;

   static bool loggingEnabled;
};

// *****************************************************************************
//                               Inline functions

inline void Logger::logDebug(
   const String& string)
{
   if (instance && loggingEnabled)
   {
      getInstance()->log(string);
   }
}

inline void Logger::logDebug(
   const char* format,
   ...)
{
   va_list arguments;
   va_start(arguments, format);

   static char sBuffer[200];
   vsnprintf(sBuffer, 200, format, arguments);

   logDebug(String(sBuffer));

   va_end(arguments);
}

inline Logger* Logger::getInstance()
{
   return (instance);
}

inline void Logger::setEnabled(
   const bool& loggingEnabled)
{
   Logger::loggingEnabled = loggingEnabled;
}

#endif  // LOGGER_H_INCLUDED
