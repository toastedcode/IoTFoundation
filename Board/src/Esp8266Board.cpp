#include "Esp8266Board.hpp"

Esp8266Board::Esp8266Board() :
   EspBoard()
{
}

Esp8266Board::~Esp8266Board()
{
}

int Esp8266Board::getChipId()
{
#ifdef ESP8266
   return (ESP.getChipId());
#else
   return (0);
#endif
}

// **************************************************************************
// Board operations

String Esp8266Board::getBoardName()
{
   return (F("ESP8266"));
}

void Esp8266Board::analogWrite(
   const int& pin,
   const int& value)
{
#ifdef ESP8266
   ::analogWrite(pin, value);
#endif
}

// **************************************************************************
// WifiBoard operations
