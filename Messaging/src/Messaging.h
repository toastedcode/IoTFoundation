#pragma once

#include "Adapter.hpp"
#include "BasicMessage.hpp"
#include "Component.hpp"
#include "MessageFactory.hpp"
#include "MessageRouter.hpp"

class Messaging
{

public:

   template <typename T>
   static void setup(
      const String& location,
      const int& messagePoolSize)
   {
      printf("Messaging::setup() \n");
      MessageRouter::setLocation(location);
      MessageFactory::allocate<T>(messagePoolSize);
      printf("Messaging::setup() end\n");
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

   // This operation sends a message to a single component.
   static bool send(
      // The message to send.
      MessagePtr message);

   // This operation sends a message to a subscribed components.
   static bool publish(
      // The message to send.
      MessagePtr message);

   static Address remoteAddress(
      const String& location,
      const String& id);

   static Address localAddress(
      const String& id);
};

inline bool Messaging::registerHandler(
   MessageHandler* handler)
{
   MessageRouter::registerHandler(handler);
}

inline bool Messaging::unregisterHandler(
   MessageHandler* handler)
{
   MessageRouter::unregisterHandler(handler);
}

inline bool Messaging::subscribe(
   MessageHandler* handler,
   Topic topic)
{
   MessageRouter::subscribe(handler, topic);
}

inline bool Messaging::unsubscribe(
   MessageHandler* handler,
   Topic topic)
{
   MessageRouter::unsubscribe(handler, topic);
}

inline MessagePtr Messaging::newMessage()
{
   return (MessageFactory::newMessage());
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

inline Address Messaging::remoteAddress(
   const String& location,
   const String& id)
{
   return (Address(location, id));
}

inline Address Messaging::localAddress(
   const String& id)
{
   return (Address(MessageRouter::getLocation(), id));
}
