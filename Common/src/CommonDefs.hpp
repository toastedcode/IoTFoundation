#pragma once

#define ARDUINO
#ifndef ARDUINO
#include <string>
typedef std::string String;
#else
#include "Arduino.h"
#endif
