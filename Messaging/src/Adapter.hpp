// *****************************************************************************
// *****************************************************************************
// Adapter.hpp
//
// Author: Jason Tost
// Date:   5.26.2016
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "Component.hpp"

class Adapter : public Component
{

public:

   Adapter(
      const String& id);

   virtual ~Adapter();

   virtual bool match(
      const Address& address);

   virtual void loop();

   virtual void handleMessage(
      MessagePtr message);

   virtual bool sendRemoteMessage(
      MessagePtr message) = 0;

   virtual MessagePtr getRemoteMessage() = 0;

protected:

};

inline Adapter::~Adapter()
{
   delete (messageQueue);
}

inline bool Adapter::match(
   const Address& address)
{
   return (address.location == id);
}
