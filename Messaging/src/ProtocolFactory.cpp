#include "ProtocolFactory.hpp"
#include "Logger.hpp"

ProtocolConstructorRegistry ProtocolFactory::registry;

void ProtocolFactory::registerProtocol(
   const String& name,
   ProtocolConstructor constructor)
{
    // Register the class constructor.
   registry[name] = constructor;

   Logger::logDebugFinest(F("ProtocolFactory::registerProtocol: Registered Protocol [%s]."), name.c_str());
}

Protocol* ProtocolFactory::create(
   const String& classId)
{
   Protocol* Protocol = 0;

   Map<String, ProtocolConstructor>::Iterator foundIt = registry.find(classId);

   if (foundIt != registry.end())
   {
      const ProtocolConstructor* constructor = &(foundIt->second);

      if (constructor)
      {
         Protocol = (*constructor)();

         Logger::logDebugFinest(F("ProtocolFactory::create: Created new %s Protocol."), classId.c_str());
      }
      else
      {
         Logger::logWarning(F("ProtocolFactory::create: No Protocol registered under class id [%s]."), classId.c_str());
      }
   }

   return (Protocol);
}
