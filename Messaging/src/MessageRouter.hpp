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

#include "../../STL/List.hpp"
#include "../../STL/Map.hpp"
#include "../../STL/Set.hpp"
#include "Message.hpp"
#include "MessageHandler.hpp"

typedef ListMap<String, MessageHandler*> MessageHandlerMap;

typedef ListSet<MessageHandler*> MessageHandlerSet;

typedef ListMap<Topic, MessageHandlerSet> SubscriptionMap;

class MessageRouter
{

public:

   static bool registerHandler(
      // The handler to be registered.
      MessageHandler* handler,
      // A flag indicating if this should be the default handler for unaddressed messages.
      const bool& setDefaultHandler = false);

   static bool unregisterHandler(
      // The handler to be unregistered.
      MessageHandler* handler);

   static bool isRegistered(
      // The handler in question.
      MessageHandler* handler);

   static bool isRegistered(
      // The id of the handler in question.
      const String& handlerId);

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

   // This operation returns true if the specifed message handler matches a message's destination.
   static bool match(
      // The message.
      const MessagePtr message,
      // The message handler to evaluate.
      const MessageHandler* handler);

   static MessageHandlerMap handlers;

   static MessageHandler* defaultHandler;

   static SubscriptionMap subscriptions;
};
