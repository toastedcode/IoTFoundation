#pragma once

#ifndef ARDUINO

#include <string>
#include "StdString.hpp"
typedef StdString String;

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define F(expression) expression
#define PROGMEM
#define FPSTR(expression) expression

#else

#include "Arduino.h"

#endif
