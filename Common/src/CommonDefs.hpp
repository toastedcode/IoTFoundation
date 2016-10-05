#pragma once

//#define ARDUINO
#ifndef ARDUINO
#include <string>
#include "StdString.hpp"
typedef StdString String;
#else
#include "Arduino.h"
#endif
