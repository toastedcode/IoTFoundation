#pragma once

#ifdef ESP8266
   #include <ESP8266WiFi.h>
#elif defined(ESP32)
   #include <WiFi.h>
#else
   #error "Unsupported ESP board."
#endif
