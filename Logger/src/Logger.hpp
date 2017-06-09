// *****************************************************************************
// *****************************************************************************
// Logger.hpp
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include <stdarg.h>

#include "CommonDefs.hpp"

// *****************************************************************************
//                               LogLevel enum

enum LogLevel
{
   DEBUG,
   INFO,
   WARNING,
   SEVERE
};

inline String toString(
   const LogLevel& logLevel)
{
   static const String enumToString[]
   {
      "DEBUG",
      "INFO",
      "WARNING",
      "SEVERE"
   };

   return (enumToString[logLevel]);
}

// *****************************************************************************

class Logger
{

public:

   Logger();

   virtual ~Logger();

   static void setLogger(
      Logger* logger);

   static void setEnabled(
      const bool& loggingEnabled);

   static void logDebug(
      const char* format,
      ...);

   static void logInfo(
      const char* format,
      ...);

   static void logWarning(
      const char* format,
      ...);

   static void logSevere(
      const char* format,
      ...);

protected:

   static Logger* getInstance();

   virtual void log(
      const LogLevel& logLevel,
      const String& string) = 0;

private:

   static Logger* instance;

   static bool loggingEnabled;
};

// *****************************************************************************
//                               Inline functions

inline Logger::Logger()
{

}

inline Logger::~Logger()
{

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
