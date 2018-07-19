#include "Logger.h"
#include "Map.hpp"
#include "Set.hpp"

void setup()
{
   Serial.begin(9600);
   Logger::setLogger(new SerialLogger());

   Logger::logDebug("\n\n********** STL Map Test **********\n\n");

   Map<int, int> myMap;

   for (int i = 0; i < 10; i++)
   {
      myMap[i] = (i * 2);
   }

   for (Map<int, int>::Iterator it = myMap.begin(); it != myMap.end(); it++)
   {
      Logger::logDebug("%d:%d", it->first, it->second);
   }
}

void loop()
{
}
