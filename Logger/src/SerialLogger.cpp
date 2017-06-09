// *****************************************************************************
// *****************************************************************************
// SerialLogger.cpp
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include "SerialLogger.hpp"

SerialLogger::SerialLogger() : Logger()
{
}

SerialLogger::~SerialLogger()
{
}

void SerialLogger::log(
   const LogLevel& logLevel,
   const String& string)
{
   Serial.print(toString(logLevel) + " ");
   Serial.print(string);
   Serial.print("\n");
}
