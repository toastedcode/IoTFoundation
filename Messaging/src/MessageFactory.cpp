// *****************************************************************************
// *****************************************************************************
// MessageFactory.cpp
//
// Author: Jason Tost
// Date:   6.3.2016
//
// *****************************************************************************
// *****************************************************************************

#include "Logger.hpp"
#include "MessageFactory.hpp"

MessagePtr* MessageFactory::messagePool = NULL;

int MessageFactory::numberOfMessages = 0;

MessagePtr MessageFactory::newMessage()
{
   MessagePtr message = getFreeMessage();

   if (message == NULL)
   {
      Logger::logDebug("Insufficient message allocation.");
   }
   else
   {
      message->initialize();
      message->setInUse();
   }

   return (message);
}

MessagePtr MessageFactory::newMessage(
   MessagePtr copyMessage)
{
   MessagePtr message = getFreeMessage();

   if (message == NULL)
   {
      Logger::logDebug("Insufficient message allocation.");
   }
   else
   {
      message->initialize(*copyMessage);
      message->setInUse();
   }

   return (message);
}

MessagePtr MessageFactory::getFreeMessage()
{
   MessagePtr message = 0;

   for (int i = 0; i < numberOfMessages; i++)
   {
      if (messagePool[i]->isFree() == true)
      {
         message = messagePool[i];
         message->setInUse();
         break;
      }
   }

   return (message);
}

int MessageFactory::freeSize()
{
   int count = 0;

   for (int i = 0; i < numberOfMessages; i++)
   {
      if (messagePool[i]->isFree() == true)
      {
         count++;
      }
   }

   return (count);
}
