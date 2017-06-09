// *****************************************************************************
// *****************************************************************************
// SerialLogger.h
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "Logger.h"

class SerialLogger : public Logger
{

public:

   SerialLogger();

   virtual ~SerialLogger();

   virtual void log(
      const LogLevel& logLevel,
      const String& string);
};
