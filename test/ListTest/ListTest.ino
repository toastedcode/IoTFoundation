#include "Logger.h"
#include "List.hpp"

void setup()
{
   Serial.begin(9600);
   Logger::setLogger(new SerialLogger());

   Logger::logDebug("\n\n********** STL List Test **********\n\n");

   List<int> list;

   for (int i = 0; i < 10; i++)
   {
      list.push_back(i);
   }

   for (int i = 0; i < 10; i++)
   {
     for (List<int>::Iterator it = list.begin(); it != list.end(); it++)
     {
        Logger::logDebug("%d", *it);
     }
   }
}

void loop()
{
}
