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
   LOG_LEVEL_FIRST,
   DEBUG_FINEST = LOG_LEVEL_FIRST,
   DEBUG,
   INFO,
   WARNING,
   SEVERE,
   LOG_LEVEL_LAST
};

inline String toString(
   const LogLevel& logLevel)
{
   static const String enumToString[] =
   {
      "DEBUG_FINEST",
      "DEBUG",
      "INFO",
      "WARNING",
      "SEVERE"
   };

   return (enumToString[logLevel]);
}

LogLevel fromString(
   const String& logLevelString);

// *****************************************************************************

class Logger
{

public:

   Logger();

   virtual ~Logger();

   static void setLogger(
      Logger* logger);

   static void setLogLevel(
      const LogLevel& logLevel);

   static LogLevel getLogLevel();

   static void setEnabled(
      const bool& loggingEnabled);

   static void logDebugFinest(
      const char* format,
      ...);

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

   static void logAt(
      const LogLevel& logLevel,
      const char* format,
      ...);

#ifdef ARDUINO
   static void logDebugFinest(
      const __FlashStringHelper* format,
      ...);

   static void logDebug(
      const __FlashStringHelper* format,
      ...);

   static void logInfo(
      const __FlashStringHelper* format,
      ...);

   static void logWarning(
      const __FlashStringHelper* format,
      ...);

   static void logSevere(
      const __FlashStringHelper* format,
      ...);

   static void logAt(
      const LogLevel& logLevel,
      const __FlashStringHelper* format,
      ...);

#endif

protected:

   static Logger* getInstance();

   virtual void log(
      const LogLevel& logLevel,
      const String& string) = 0;

private:

   // Compares the specified log level to Logger::logLevel and returns true if
   // the logger should log.
   static bool shouldLog(LogLevel logLevel);

   static const int BUFFER_SIZE = 512;  // bytes

   static Logger* instance;

   static bool loggingEnabled;

   static LogLevel logLevel;

   static char sBuffer[BUFFER_SIZE];

   static bool recursionGuard;
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

inline bool Logger::shouldLog(LogLevel logLevel)
{
   return (logLevel >= Logger::logLevel);
}
