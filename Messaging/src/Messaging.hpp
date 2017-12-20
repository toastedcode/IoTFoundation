#pragma once

#include "MessageFactory.hpp"
#include "MessageRouter.hpp"

class Messaging
{

public:

   template <typename T>
   static void setup(
      const int& messagePoolSize)
   {
      MessageFactory::allocate<T>(messagePoolSize);
   }

   static bool registerHandler(
      MessageHandler* handler);

   static bool unregisterHandler(
      MessageHandler* handler);

   static bool subscribe(
      // The handler to be subscribed.
      MessageHandler* handler,
      // The topic to which the handler should be subscribed.
      Topic topic);

   static bool unsubscribe(
      // The handler to be unsubscribed.
      MessageHandler* handler,
      // The topic to which the handler should be unsubscribed.
      Topic topic);

   static MessagePtr newMessage();

   static MessagePtr copyMessage(
      MessagePtr message);

   // This operation sends a message to a single component.
   static bool send(
      // The message to send.
      MessagePtr message);

   // This operation sends a message to a subscribed components.
   static bool publish(
      // The message to send.
      MessagePtr message);
};

inline bool Messaging::registerHandler(
   MessageHandler* handler)
{
   return (MessageRouter::registerHandler(handler));
}

inline bool Messaging::unregisterHandler(
   MessageHandler* handler)
{
   return (MessageRouter::unregisterHandler(handler));
}

inline bool Messaging::subscribe(
   MessageHandler* handler,
   Topic topic)
{
   return (MessageRouter::subscribe(handler, topic));
}

inline bool Messaging::unsubscribe(
   MessageHandler* handler,
   Topic topic)
{
   return (MessageRouter::unsubscribe(handler, topic));
}

inline MessagePtr Messaging::newMessage()
{
   return (MessageFactory::newMessage());
}

inline MessagePtr Messaging::copyMessage(
   MessagePtr message)
{
   return (MessageFactory::newMessage(message));
}

inline bool Messaging::send(
   MessagePtr message)
{
   return (MessageRouter::send(message));
}

inline bool Messaging::publish(
   MessagePtr message)
{
   return (MessageRouter::publish(message));
}
