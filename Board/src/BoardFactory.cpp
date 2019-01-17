#include "BoardFactory.hpp"
#include "Logger.hpp"

BoardConstructorRegistry BoardFactory::registry;

void BoardFactory::registerBoard(
   const String& name,
   BoardConstructor constructor)
{
    // Register the class constructor.
   registry[name] = constructor;

   Logger::logDebugFinest(F("BoardFactory::registerBoard: Registered board [%s]."), name.c_str());
}

Board* BoardFactory::create(
   const String& classId)
{
   Board* board = 0;

   Map<String, BoardConstructor>::Iterator foundIt = registry.find(classId);

   if (foundIt != registry.end())
   {
      const BoardConstructor* constructor = &(foundIt->second);

      if (constructor)
      {
         board = (*constructor)();

         Logger::logDebugFinest(F("BoardFactory::create: Created new %s board."), classId.c_str());
      }
      else
      {
         Logger::logWarning(F("BoardFactory::create: No board registered under class id [%s]."), classId.c_str());
      }
   }

   return (board);
}
