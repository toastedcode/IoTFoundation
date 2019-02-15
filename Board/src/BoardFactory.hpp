#pragma once

#include "../../STL/Map.hpp"
#include "Board.hpp"

#define REGISTER_BOARD(CLASS_NAME, CLASS_STRING) static const BoardCreator<CLASS_NAME> CLASS_NAME ## Creator(#CLASS_STRING);

// *****************************************************************************
//                               Typedefs
// *****************************************************************************

typedef Board* (*BoardConstructor)();

typedef Map<String, BoardConstructor> BoardConstructorRegistry;

// *****************************************************************************
//                           BoardFactory
// *****************************************************************************

class BoardFactory
{

public:

   static void registerBoard(
      const String& classId,
      BoardConstructor constructor);

   static Board* create(
      const String& classId);

private:

   static BoardConstructorRegistry& getRegistry()
   {
      // Note: This construct-on-first-use idiom helps us avoid the static initialization order fiasco.
      static BoardConstructorRegistry* registry = new BoardConstructorRegistry();

      return (*registry);
   }
};

// *****************************************************************************
//                           BoardCreator
// *****************************************************************************

template <class T>
class BoardCreator
{

public:

   BoardCreator(
      const String& classId)
   {
      BoardFactory::registerBoard(classId, create);
   }

   static Board* create()
   {
      return (new T());
   }
};
