#pragma once

#include "Component.hpp"
#include "ListMap.hpp"
#include "Messaging.hpp"

#define REGISTER(CLASS_NAME, CLASS_STRING) static const ComponentCreator<CLASS_NAME> CLASS_NAME ## Creator(#CLASS_STRING);

// *****************************************************************************
//                               Typedefs
// *****************************************************************************

typedef Component* (*ComponentConstructor)(MessagePtr);

typedef ListMap<String, ComponentConstructor> ConstructorRegistry;

// *****************************************************************************
//                           ComponentFactory
// *****************************************************************************

class ComponentFactory
{

public:

   static void registerComponent(
      const String& classId,
      ComponentConstructor constructor);

   static Component* create(
      const String& classId,
      MessagePtr message);

   static ConstructorRegistry registry;
};

// *****************************************************************************
//                           ComponentCreator
// *****************************************************************************

template <class T>
class ComponentCreator
{

public:

   ComponentCreator(
      const String& classId)
   {
      ComponentFactory::registerComponent(classId, create);
   }

   static Component* create(
      MessagePtr message)
   {
      return (new T(message));
   }
};
