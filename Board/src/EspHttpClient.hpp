#pragma once

#ifdef ESP8266
   #include <ESP8266HTTPClient.h>
#elif defined(ESP32)
   #include <HTTPClient.h>
#else
   #error "Unsupported ESP board."
#endif
