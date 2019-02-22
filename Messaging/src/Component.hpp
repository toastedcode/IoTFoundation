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

class Component : public MessageHandler
{

public:

   Component(
      const String& id);

   Component(
      MessagePtr message);

   virtual ~Component();

   virtual String getId() const;

   virtual bool queueMessage(
      MessagePtr message);

   virtual void setup();

   virtual void loop();

   virtual void handleMessage(
      MessagePtr message);

protected:

   virtual MessagePtr pingReply(
      MessagePtr ping);

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

inline bool Component::queueMessage(
   MessagePtr message)
{
   return (messageQueue->enqueue(message));
}

inline void Component::setup()
{
   // Nothing to do here.
}
