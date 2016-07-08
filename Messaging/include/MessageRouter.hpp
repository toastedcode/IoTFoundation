// *****************************************************************************
// *****************************************************************************
// MessageRouter.hpp
//
// Author: Jason Tost
// Date:   5.25.2016
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include <list>
#include <map>

#include "Message.hpp"
#include "MessageHandler.hpp"

typedef std::map<Address, MessageHandler*> MessageHandlerMap;

typedef std::list<MessageHandler*> MessageHandlerList;

typedef std::map<Topic, MessageHandlerList> SubscriptionMap;

class MessageRouter
{

public:

   static void setLocation(
      const String& location);

   static String getLocation();

   static bool registerHandler(
      // The handler to be registered.
      MessageHandler* handler);

   static bool unregisterHandler(
      // The handler to be unregistered.
      MessageHandler* handler);

   static bool isRegistered(
      // The handler in question.
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

   static bool isSubscribed(
      // The handler in question.
      MessageHandler* handler,
      // The topic in question.
      Topic topic);

   // This operation sends a message to a single component.
   static bool send(
      // The message to send.
      MessagePtr message);

   // This operation sends a message to a subscribed components.
   static bool publish(
      // The message to send.
      MessagePtr message);

private:

   static String location;

   static MessageHandlerMap handlers;

   static SubscriptionMap subscriptions;
};

inline void MessageRouter::setLocation(
   const String& location)
{
   MessageRouter::location = location;
}

inline String MessageRouter::getLocation()
{
   return (location);
}
