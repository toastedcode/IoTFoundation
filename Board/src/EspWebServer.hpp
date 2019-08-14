#pragma once

#ifdef ESP8266
   #include <ESP8266WebServer.h>
   #define EspWebServer ESP8266WebServer
#elif defined(ESP32)
   #include <WebServer.h>
   #define EspWebServer WebServer
#else
   #error "Unsupported ESP board."
#endif
