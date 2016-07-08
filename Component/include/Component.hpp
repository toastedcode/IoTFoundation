// *****************************************************************************
// *****************************************************************************
// Component.hpp
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

typedef String String;

class Component : public MessageHandler
{

public:

   Component(
      const String& id);

   virtual ~Component();

   virtual String getId() const;

   virtual Address getAddress() const;

   virtual bool match(
      const Address& address);

   virtual bool queueMessage(
      MessagePtr message);

   virtual void loop();

   virtual void handleMessage(
      MessagePtr message) = 0;

protected:

   String id;

   MessageQueue* messageQueue;
};

inline Component::~Component()
{
   delete (messageQueue);
}

inline String Component::getId() const
{
   return (id);
}

inline Address Component::getAddress() const
{
   return (Address(MessageRouter::getLocation(), id));
}

inline bool Component::match(
   const Address& address)
{
   return (address == getAddress());
}

inline bool Component::queueMessage(
   MessagePtr message)
{
   return (messageQueue->enqueue(message));
}
