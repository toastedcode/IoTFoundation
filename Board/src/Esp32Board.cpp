#include "Esp32Board.hpp"

Esp32Board::Esp32Board() :
   EspBoard()
{
}

Esp32Board::~Esp32Board()
{
}

int Esp32Board::getChipId()
{
#ifdef ESP32
   // TODO
   return (0);
#else
   return (0);
#endif
}

// **************************************************************************
// Board operations

String Esp32Board::getBoardName()
{
   return (F("ESP32"));
}

void Esp32Board::analogWrite(
   const int& pin,
   const int& value)
{
#ifdef ESP32
   // TODO
#endif
}

// **************************************************************************
// WifiBoard operations
