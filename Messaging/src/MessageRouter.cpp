// *****************************************************************************
// *****************************************************************************
// MessageRouter.cpp
//
// Author: Jason Tost
// Date:   5.25.2016
//
// *****************************************************************************
// *****************************************************************************

#include "MessageFactory.hpp"
#include "MessageRouter.hpp"

String MessageRouter::location;

MessageHandlerMap MessageRouter::handlers;

SubscriptionMap MessageRouter::subscriptions;

bool MessageRouter::registerHandler(
   MessageHandler* handler)
{
   if (isRegistered(handler) == false)
   {
      handlers[handler->getAddress()] = handler;
      printf("MessageRouter::registerHandler: Registered message handler [%s]\n", handler->getAddress().toString().c_str());
   }

   return (true);
}

bool MessageRouter::unregisterHandler(
   MessageHandler* handler)
{
   handlers.erase(handler->getAddress());
   printf("MessageRouter::registerHandler: Registered message handler [%s]\n", handler->getAddress().toString().c_str());

   return (true);
}

bool MessageRouter::isRegistered(
   MessageHandler* handler)
{
   return (handlers.find(handler->getAddress()) != handlers.end());
}

bool MessageRouter::subscribe(
   MessageHandler* handler,
   Topic topic)
{
   if (isSubscribed(handler, topic) == false)
   {
      subscriptions[topic].push_back(handler);
      printf("MessageRouter::subscribe: Message handler [%s] subscribed to topic [%s]\n", handler->getAddress().toString().c_str(), topic.c_str());
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
   MessageHandlerList topicHandlers = subscriptions[topic];
   return (std::find(topicHandlers.begin(), topicHandlers.end(), handler) != topicHandlers.end());
}

bool MessageRouter::send(
   MessagePtr message)
{
   bool success = false;

   printf("Trying to send to %s\n", message->getDestination().toString().c_str());

   MessageHandlerMap::iterator findIt;
   for (findIt = handlers.begin(); findIt != handlers.end(); findIt++)
   {
      if (findIt->second->match(message->getDestination()))
      {
         success = findIt->second->queueMessage(message);
         break;
      }
   }

   if (findIt == handlers.end())
   {
      // Logging.
   }

   return (success);
}

bool MessageRouter::publish(
   MessagePtr message)
{
   bool success = true;

   MessageHandlerList topicHandlers = subscriptions[message->getTopic()];

   for (MessageHandlerList::const_iterator it = topicHandlers.begin(); it != topicHandlers.end(); it++)
   {
      MessagePtr broadcastMessage = MessageFactory::newMessage(message);

      success &= ((broadcastMessage) &&
                       ((*it)->queueMessage(broadcastMessage)));
   }

   message->setFree();

   return (success);
}
