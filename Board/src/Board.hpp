// *****************************************************************************
// *****************************************************************************
// Board.hpp
//
// Author: Jason Tost
// Date:   10.17.2016
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "Common.h"  // TODO: For the life of me, I can't figure out why I can't directly include CommonDefs.hpp!

class Board
{

public:

   // Destructor.
   virtual ~Board() = 0;

   static Board* getBoard();

   static void setBoard(
      Board* board);

   virtual String getBoardName() = 0;

   virtual void pinMode(
      const int& pin,
      const int& mode) = 0;

   virtual int analogRead(
      const int& pin) = 0;

   virtual void analogWrite(
      const int& pin,
      const int& value) = 0;

   virtual int digitalRead(
      const int& pin) = 0;

   virtual void digitalWrite(
      const int& pin,
      const int& value) = 0;

   virtual void reset() = 0;

   virtual void lightSleep(
      const long& milliseconds) = 0;

   virtual void deepSleep(
      const long& milliseconds) = 0;

   virtual int systemTime() const = 0;

private:

   static Board* instance;
};

inline Board::~Board() {}

inline Board* Board::getBoard()
{
   return (instance);
}

inline void Board::setBoard(
   Board* board)
{
   instance = board;
}
