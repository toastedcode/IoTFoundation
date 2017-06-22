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
#include "MessageFactory.hpp"
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
   id = (message->isSet("id")) ? message->getString("id") : "motor";

   messageQueue = new StaticMessageQueue(QUEUE_SIZE);
}

void Component::loop()
{
   MessagePtr message = 0;

   message = messageQueue->dequeue();
   while (message)
   {
      handleMessage(message);

      message->setFree();

      message = messageQueue->dequeue();
   }
}


void Component::handleMessage(
   MessagePtr message)
{
   //  ping
   if (message->getMessageId() == "ping")
   {
      Message* reply = MessageFactory::newMessage();

      reply->setMessageId("pong");
      reply->setSource(getId());
      reply->setDestination(message->getSource());

      MessageRouter::send(reply);
   }
   else
   {
      Logger::logDebugFinest(
         "Component::handleMessage: Unhandled message [%s] in component [%s].\n",
         message->getMessageId().c_str(),
         getId().c_str());
   }

   message->setFree();
}
