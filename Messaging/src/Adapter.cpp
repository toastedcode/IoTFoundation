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
#include "Address.hpp"
#include "MessageRouter.hpp"
#include "StaticMessageQueue.hpp"

Adapter::Adapter(
   const String& id,
   Protocol* protocol) :
      Component(id),
      protocol(protocol)
{
}

void Adapter::handleMessage(
   MessagePtr message)
{
   // Remove our id from the destination address.
   // Ex. adapterId@remoteId -> remoteId
   Address dest(message->getDestination());
   dest.pop();
   message->setDestination(dest.toString());

   sendRemoteMessage(message);
   message->setFree();
}

void Adapter::loop()
{
   MessagePtr message = 0;

   //
   // Send
   //

   Component::loop();

   //
   // Receive
   //

   message = getRemoteMessage();
   while (message)
   {
      // Add our id to the source address.
      // Ex. remoteId -> adapterId@remoteId
      Address src(message->getSource());
      src.push(getId());
      message->setSource(src.toString());

      if (message->getTopic().length() > 0)
      {
         MessageRouter::publish(message);
      }
      else
      {
         MessageRouter::send(message);
      }

      message = getRemoteMessage();
   }
}
