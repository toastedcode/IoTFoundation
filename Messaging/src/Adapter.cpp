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
#include "MessagePool.hpp"
#include "MessageRouter.hpp"
#include "ProtocolFactory.hpp"
#include "StaticMessageQueue.hpp"

Adapter::Adapter(
   const String& id,
   Protocol* protocol) :
      Component(id),
      protocol(protocol)
{
}

Adapter::Adapter(
   MessagePtr parameters) :
      Component(parameters)
{
   protocol = ProtocolFactory::create(parameters->getString("protocol"));
}

void Adapter::handleMessage(
   MessagePtr message)
{
   // Remove our id from the destination address.
   // Ex. adapterId@remoteId -> remoteId
   Address dest(message->getDestination());
   dest.pop();

   String destination = dest.toString();

   if (destination.length() > 0)
   {
      message->setDestination(destination);
   }
   else
   {
      message->unset("destination");
   }

   sendRemoteMessage(message);
   MessagePool::freeMessage(message);
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
