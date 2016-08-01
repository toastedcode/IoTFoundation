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
#include "Protocol.hpp"

class Adapter : public Component
{

public:

   Adapter(
      const String& id,
      Protocol* protocol);

   virtual ~Adapter();

   void setProtocol(
      Protocol* protocol);

   virtual bool match(
      const Address& address);

   virtual void loop();

   virtual void handleMessage(
      MessagePtr message);

   virtual bool sendRemoteMessage(
      MessagePtr message) = 0;

   virtual MessagePtr getRemoteMessage() = 0;

protected:

   Protocol* protocol;

};

inline Adapter::~Adapter()
{
   delete (messageQueue);
}

inline void Adapter::setProtocol(
   Protocol* protocol)
{
   this->protocol = protocol;
}

inline bool Adapter::match(
   const Address& address)
{
   return (address.location == id);
}
