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

#include "MessageHandler.hpp"
#include "MessageQueue.hpp"
#include "MessageRouter.hpp"

class Adapter : public MessageHandler
{

public:

   Adapter(
      const String& id);

   virtual ~Adapter();

   virtual String getId() const;

   virtual Address getAddress() const;

   virtual bool match(
      const Address& address);

   virtual bool queueMessage(
      MessagePtr message);

   virtual void loop();

   virtual bool sendRemoteMessage(
      MessagePtr message) = 0;

   virtual MessagePtr getRemoteMessage() = 0;

protected:

   String id;

   String remoteLocation;

   MessageQueue* messageQueue;
};

inline Adapter::~Adapter()
{
   delete (messageQueue);
}

inline String Adapter::getId() const
{
   return (id);
}

inline Address Adapter::getAddress() const
{
   return (Address(MessageRouter::getLocation(), id));
}

inline bool Adapter::match(
   const Address& address)
{
   return (address.location == id);
}

inline bool Adapter::queueMessage(
   MessagePtr message)
{
   return (messageQueue->enqueue(message));
}
