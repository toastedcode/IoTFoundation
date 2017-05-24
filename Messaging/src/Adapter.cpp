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
      message->setSource(getId());

      MessageRouter::send(message);

      message = getRemoteMessage();
   }
}
