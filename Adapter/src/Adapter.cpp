// *****************************************************************************
// *****************************************************************************
// Adapter.cpp
//
// Author: Jason Tost
// Date:   7.6.2016
//
// *****************************************************************************
// *****************************************************************************

#include "Adapter.hpp"
#include "MessageRouter.hpp"
#include "StaticMessageQueue.hpp"

static const int QUEUE_SIZE = 10;

Adapter::Adapter(
   const String& id) :
      id(id)
{
   messageQueue = new StaticMessageQueue(QUEUE_SIZE);
}

void Adapter::loop()
{
   MessagePtr message = NULL;

   //
   // Send
   //

   message = messageQueue->dequeue();
   while (message != NULL)
   {
      sendRemoteMessage(message);

      message = messageQueue->dequeue();
   }

   //
   // Receive
   //

   message = getRemoteMessage();
   while (message != NULL)
   {
      MessageRouter::send(message);

      message = getRemoteMessage();
   }
}
