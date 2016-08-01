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
   const String& id,
   Protocol* protocol) : Component(id),
                         protocol(protocol)
{
}

void Adapter::handleMessage(
   MessagePtr message)
{
   sendRemoteMessage(message);
   message->setFree();
}

void Adapter::loop()
{
   MessagePtr message = NULL;

   //
   // Send
   //

   Component::loop();

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
