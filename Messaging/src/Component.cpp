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
#include "StaticMessageQueue.hpp"

static const int QUEUE_SIZE = 10;

Component::Component(
   const String& id) :
     id(id)
{
   messageQueue = new StaticMessageQueue(QUEUE_SIZE);
}

void Component::loop()
{
   MessagePtr message;

   message = messageQueue->dequeue();
   while (message != NULL)
   {
      handleMessage(message);

      message->setFree();

      message = messageQueue->dequeue();
   }
}
