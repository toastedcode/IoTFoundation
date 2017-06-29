// *****************************************************************************
// *****************************************************************************
// MessageRouter.cpp
//
// Author: Jason Tost
// Date:   5.25.2016
//
// *****************************************************************************
// *****************************************************************************

#include "Logger.hpp"
#include "MessageFactory.hpp"
#include "MessageRouter.hpp"
#include "StringUtils.hpp"

MessageHandlerMap MessageRouter::handlers;

MessageHandler* MessageRouter::defaultHandler = 0;

SubscriptionMap MessageRouter::subscriptions;

bool MessageRouter::registerHandler(
   MessageHandler* handler,
   const bool& setDefaultHandler)
{
   if (isRegistered(handler) == false)
   {
      handlers[handler->getId()] = handler;

      Logger::logDebugFinest(
         "MessageRouter::registerHandler: Registered message handler [%s].",
         handler->getId().c_str());
   }

   if (setDefaultHandler)
   {
      defaultHandler = handler;
   }

   return (true);
}

bool MessageRouter::unregisterHandler(
   MessageHandler* handler)
{
   handlers.erase(handler->getId());

   Logger::logDebugFinest(
      "MessageRouter::registerHandler: Registered message handler [%s].",
      handler->getId().c_str());

   return (true);
}

bool MessageRouter::isRegistered(
   MessageHandler* handler)
{
   return (handlers.find(handler) != 0);
}

bool MessageRouter::isRegistered(
   const String& handlerId)
{
   return (handlers.get(handlerId) != 0);
}

bool MessageRouter::subscribe(
   MessageHandler* handler,
   Topic topic)
{
   if (isSubscribed(handler, topic) == false)
   {
      subscriptions[topic].add(handler);

      Logger::logDebugFinest(
         "MessageRouter::subscribe: Message handler [%s] subscribed to topic [%s].",
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

   // Direct un-addressed messages to the default handler.
   if ((message->getDestination() == "") &&
       (defaultHandler))
   {
      success = defaultHandler->queueMessage(message);
   }
   // Otherwise, search for a matching message handler.
   else
   {
      // TODO: Make use of MessageHandlerMap operations.
      for (int i = 0; i < handlers.length(); i++)
      {
         const MessageHandlerMap::Entry* entry = handlers.item(i);

         if (match(message, entry->value))
         {
            Logger::logDebugFinest(
               "MessageRouter::send: Dispatching message [%s] to destination [%s].",
               message->getMessageId().c_str(),
               message->getDestination().c_str());

            success = entry->value->queueMessage(message);
            break;
         }
      }
   }

   if (!success)
   {
      Logger::logDebugFinest(
         "MessageRouter::send: Failed to dispatch message [%s] to destination [%s].",
         message->getMessageId().c_str(),
         message->getDestination().c_str());

      message->setFree();
   }

   return (success);
}

bool MessageRouter::publish(
   MessagePtr message)
{
   bool success = true;

   MessageHandlerSet topicHandlers = subscriptions[message->getTopic()];

   Logger::logDebugFinest(
      "MessageRouter::publish: Broadcasting message [%s] with topic [%s] to %d subscribers.",
      message->getMessageId().c_str(),
      message->getTopic().c_str(),
      topicHandlers.length());

   for (int i = 0; i < topicHandlers.length(); i++)
   {
      MessagePtr broadcastMessage = MessageFactory::newMessage(message);

      success &= ((broadcastMessage) &&
                  topicHandlers.item(i)->value->queueMessage(broadcastMessage));
   }

   message->setFree();

   return (success);
}


bool MessageRouter::match(
   const MessagePtr message,
   const MessageHandler* handler)
{
   bool isDestination = false;

   if (message && handler)
   {
      String destinationId = message->getDestination();
      destinationId = destinationId.substring(0, StringUtils::findFirstOf(destinationId, MESSAGE_HANDLER_ID_SEPARATOR));

      isDestination = (destinationId == handler->getId());
   }

   return (isDestination);
}
