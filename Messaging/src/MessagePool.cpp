#include "CommonDefs.hpp"
#include "Logger.hpp"
#include "MessagePool.hpp"

Pool<Message>* MessagePool::messagePool = 0;

void MessagePool::setup(
   const int& messagePoolSize)
{
   messagePool = new Pool<Message>(messagePoolSize);
}

MessagePtr MessagePool::newMessage()
{
   MessagePtr message = 0;

   if (messagePool)
   {
      message = messagePool->getFree();

      if (!message)
      {
         Logger::logSevere(F("Messaging::newMessage: Insufficient message allocation."));
      }
      else
      {
         message->initialize();
      }
   }

   return (message);
}

MessagePtr MessagePool::copyMessage(
   MessagePtr copyMessage)
{
   MessagePtr message = 0;

   if (messagePool)
   {
      message = messagePool->getFree();

      if (!message)
      {
         Logger::logSevere(F("Messaging::newMessage: Insufficient message allocation."));
      }
      else
      {
         message->initialize(*copyMessage);
      }
   }

   return (message);
}

void MessagePool::freeMessage(
   MessagePtr message)
{
   messagePool->setFree(message);
}
