#pragma once

#include "../../STL/Map.hpp"
#include "Protocol.hpp"

#define REGISTER_PROTOCOL(CLASS_NAME, CLASS_STRING) static const ProtocolCreator<CLASS_NAME> CLASS_NAME ## Creator(#CLASS_STRING);

// *****************************************************************************
//                               Typedefs
// *****************************************************************************

typedef Protocol* (*ProtocolConstructor)();

typedef Map<String, ProtocolConstructor> ProtocolConstructorRegistry;

// *****************************************************************************
//                           ProtocolFactory
// *****************************************************************************

class ProtocolFactory
{

public:

   static void registerProtocol(
      const String& classId,
      ProtocolConstructor constructor);

   static Protocol* create(
      const String& classId);

   static ProtocolConstructorRegistry registry;
};

// *****************************************************************************
//                           ProtocolCreator
// *****************************************************************************

template <class T>
class ProtocolCreator
{

public:

   ProtocolCreator(
      const String& classId)
   {
      ProtocolFactory::registerProtocol(classId, create);
   }

   static Protocol* create()
   {
      return (new T());
   }
};
