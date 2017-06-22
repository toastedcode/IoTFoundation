#include "Component.hpp"
#include "Map.hpp"

template <class T>
class ComponentCreator
{

public:

   ComponentCreator(
      const String& className)
   {
      ComponentFactory::registerComponent(className, this);
   }

   Component* create(MessagePtr message) {return (new T(message));
};

class ComponentFactory
{
   static void registerComponent(
      const String& className,
      ComponentCreator* creator);

   static Component* create(
      const String& className,
      MessagePtr message);

   typedef Map<String, ComponentCreator, 20> RegistryMap;

   static RegistryMap creatorRegistry;
};

inline void ComponentFactory::registerComponent(
   const String& className,
   ComponentCreator* creator)
{
   creatorRegistry.put(String, creator);
}

inline Component* ComponentFactory::create(
   const String& className,
   MessagePtr message)
{
   Component* component = 0;

   ComponentCreator* creator = creatorRegistry.get(className);

   if (creator)
   {
      creator->create(message);
   }

   return (component);
}

static ComponentCreator<Motor> creator("motor");
