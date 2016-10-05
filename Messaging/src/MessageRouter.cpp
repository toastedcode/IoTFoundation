// *****************************************************************************
// *****************************************************************************
// MessageRouter.cpp
//
// Author: Jason Tost
// Date:   5.25.2016
//
// *****************************************************************************
// *****************************************************************************

#include "Logger.h"
#include "MessageFactory.hpp"
#include "MessageRouter.hpp"

MessageHandlerMap MessageRouter::handlers;

SubscriptionMap MessageRouter::subscriptions;

bool MessageRouter::registerHandler(
   MessageHandler* handler)
{
   if (isRegistered(handler) == false)
   {
      handlers[handler->getId()] = handler;

      Logger::logDebug("MessageRouter::registerHandler: Registered message handler [%s].\n", handler->getId().c_str());
   }

   return (true);
}

bool MessageRouter::unregisterHandler(
   MessageHandler* handler)
{
   handlers.erase(handler->getId());

   Logger::logDebug("MessageRouter::registerHandler: Registered message handler [%s].\n", handler->getId().c_str());

   return (true);
}

bool MessageRouter::isRegistered(
   MessageHandler* handler)
{
   return (handlers.find(handler) != 0);
}

bool MessageRouter::subscribe(
   MessageHandler* handler,
   Topic topic)
{
   if (isSubscribed(handler, topic) == false)
   {
      subscriptions[topic].add(handler);

      Logger::logDebug(
         "MessageRouter::subscribe: Message handler [%s] subscribed to topic [%s].\n",
         handler->getId().c_str(),
         topic.c_str());
   }

   return (true);
}

bool MessageRouter::unsubscribe(
   MessageHandler* handler,
   Topic topic)
{
   subscriptions[topic].remove(handler);

   return (true);
}

bool MessageRouter::isSubscribed(
   MessageHandler* handler,
   Topic topic)
{
   MessageHandlerSet topicHandlers = subscriptions[topic];
   return (topicHandlers.contains(handler));
}

bool MessageRouter::send(
   MessagePtr message)
{
   bool success = false;

   // TODO: Make use of MessageHandlerMap operations.
   for (int i = 0; i < handlers.length(); i++)
   {
      const MessageHandlerMap::Entry* entry = handlers.item(i);

      if (entry->key == message->getDestination())
      {
         success = entry->value->queueMessage(message);
         break;
      }
   }

   if (!success)
   {
      Logger::logDebug(
         "MessageRouter::send: Failed to dispatch message [] to destination [].\n",
         message->getMessageId().c_str(),
         message->getDestination().c_str());
   }

   return (success);
}

bool MessageRouter::publish(
   MessagePtr message)
{
   bool success = true;

   MessageHandlerSet topicHandlers = subscriptions[message->getTopic()];

   for (int i = 0; i < topicHandlers.length(); i++)
   {
      MessagePtr broadcastMessage = MessageFactory::newMessage(message);

      success &= ((broadcastMessage) &&
                  topicHandlers.item(i)->value->queueMessage(broadcastMessage));
   }

   message->setFree();

   return (success);
}
