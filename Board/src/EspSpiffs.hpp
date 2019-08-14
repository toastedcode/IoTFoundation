#pragma once

#ifdef ESP8266
   #include <FS.h>
#elif defined(ESP32)
   #include <FS.h>
   #include <SPIFFS.h>
#else
   #error "Unsupported ESP board."
#endif
