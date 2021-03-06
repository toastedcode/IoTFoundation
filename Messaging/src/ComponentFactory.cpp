#include "ComponentFactory.hpp"
#include "Logger.hpp"

ConstructorRegistry ComponentFactory::registry;

void ComponentFactory::registerComponent(
   const String& name,
   ComponentConstructor constructor)
{
    // Register the class constructor.
   registry[name] = constructor;

   Logger::logDebugFinest(F("ComponentFactory::registerComponent: Registered component [%s]."), name.c_str());
}

Component* ComponentFactory::create(
   const String& classId,
   MessagePtr message)
{
   Component* component = 0;

   Map<String, ComponentConstructor>::Iterator foundIt = registry.find(classId);

   if (foundIt != registry.end())
   {
      const ComponentConstructor* constructor = &(foundIt->second);

      if (constructor)
      {
         component = (*constructor)(message);

         Logger::logDebugFinest(F("ComponentFactory::create: Created new %s component."), classId.c_str());
      }
      else
      {
         Logger::logWarning(F("ComponentFactory::create: No component registered under class id [%s]."), classId.c_str());
      }
   }

   return (component);
}
