#pragma once

#include "Message.hpp"

class Protocol
{

public:

   virtual bool parse(
      const String& messageString,
      MessagePtr message) = 0;

   virtual String serialize(
      MessagePtr message) const = 0;
};
