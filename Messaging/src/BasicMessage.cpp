#pragma once

#include "BasicMessage.hpp"


bool BasicMessage::getBool(ParameterName name) const
{
   bool b = false;

   const String* value = parameters.get(name);
   if (value != 0)
   {
      String lowerCase = *value;
      lowerCase.toLowerCase();

      b = (lowerCase == "true");
   }

   return (b);
}
