// *****************************************************************************
// *****************************************************************************
// Esp32Board.hpp
//
// Author: Jason Tost
// Date:   8.8.2019
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "BoardFactory.hpp"
#include "EspBoard.hpp"

class Esp32Board : public EspBoard
{

public:

   // Constructor.
   Esp32Board();

   // Destructor.
   virtual ~Esp32Board();

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

REGISTER_BOARD(Esp32Board, Esp32Board)
