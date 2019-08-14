// *****************************************************************************
// *****************************************************************************
// Esp8266Board.hpp
//
// Author: Jason Tost
// Date:   10.17.2016
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "BoardFactory.hpp"
#include "EspBoard.hpp"

class Esp8266Board : public EspBoard
{

public:

   // Constructor.
   Esp8266Board();

   // Destructor.
   virtual ~Esp8266Board();

   virtual int getChipId();

   // **************************************************************************
   // Board operations.

   virtual String getBoardName();

   virtual void analogWrite(
      const int& pin,
      const int& value);

   // **************************************************************************
   // WifiBoard operations.

};

REGISTER_BOARD(Esp8266Board, Esp8266Board)
