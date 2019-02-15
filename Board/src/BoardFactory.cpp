#include "BoardFactory.hpp"
#include "Logger.hpp"

void BoardFactory::registerBoard(
   const String& name,
   BoardConstructor constructor)
{
   // Register the class constructor.
   getRegistry()[name] = constructor;

   Logger::logDebugFinest(F("BoardFactory::registerBoard: Registered board [%s]."), name.c_str());
}

Board* BoardFactory::create(
   const String& classId)
{
   Board* board = 0;

   Map<String, BoardConstructor>::Iterator foundIt = getRegistry().find(classId);

   if (foundIt != getRegistry().end())
   {
      const BoardConstructor* constructor = &(foundIt->second);

      if (constructor)
      {
         board = (*constructor)();

         Logger::logDebugFinest(F("BoardFactory::create: Created new %s board."), classId.c_str());
      }
      else
      {
         Logger::logWarning(F("BoardFactory::create: No board constructor registered under class id [%s]."), classId.c_str());
      }
   }
   else
   {
      Logger::logWarning(F("BoardFactory::create: No board registered under class id [%s]."), classId.c_str());
   }

   return (board);
}
