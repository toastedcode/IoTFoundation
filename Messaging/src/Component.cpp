// *****************************************************************************
// *****************************************************************************
// Component.cpp
//
// Author: Jason Tost
// Date:   7.66.2016
//
// *****************************************************************************
// *****************************************************************************

#include "Component.hpp"
#include "Logger.hpp"
#include "MessagePool.hpp"
#include "MessageRouter.hpp"
#include "StaticMessageQueue.hpp"

static const int QUEUE_SIZE = 10;

Component::Component(
   const String& id) :
     id(id)
{
   messageQueue = new StaticMessageQueue(QUEUE_SIZE);
}

Component::Component(
   MessagePtr message)
{
   id = message->getString("id");

   messageQueue = new StaticMessageQueue(QUEUE_SIZE);
}

void Component::loop()
{
   MessagePtr message = 0;

   message = messageQueue->dequeue();
   while (message)
   {
      handleMessage(message);

      MessagePool::freeMessage(message);

      message = messageQueue->dequeue();
   }
}


void Component::handleMessage(
   MessagePtr message)
{
   //  ping
   if (message->getMessageId() == "ping")
   {
      Message* reply = pingReply(message);

      if (reply)
      {
         MessageRouter::send(reply);
      }
   }
   else
   {
      Logger::logDebugFinest(
         F("Component::handleMessage: Unhandled message [%s] in component [%s].\n"),
         message->getMessageId().c_str(),
         getId().c_str());
   }

   MessagePool::freeMessage(message);
}

MessagePtr Component::pingReply(
   MessagePtr ping)
{
   MessagePtr reply = MessagePool::newMessage();

   if (reply)
   {
      reply->setMessageId("pong");
      reply->setSource(getId());

      if (ping)
      {
         reply->setDestination(ping->getSource());
      }
   }

   return (reply);
}
