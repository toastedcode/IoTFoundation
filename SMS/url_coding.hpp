// From: https://github.com/zenmanenergy/ESP8266-Arduino-Examples/blob/master/helloWorld_urlencoded/urlencode.ino

#pragma once

#include "CommonDefs.hpp"

unsigned char h2int(char c);
String urldecode(String str);
String urlencode(String str);
