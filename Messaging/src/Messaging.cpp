#include "CommonDefs.hpp"
#include "Logger.hpp"
#include "Messaging.hpp"
#include "MessagePool.hpp"
#include "MessageRouter.hpp"

void Messaging::setup(
   const int& messagePoolSize)
{
   MessagePool::setup(messagePoolSize);
}

bool Messaging::registerHandler(
   MessageHandler* handler)
{
   return (MessageRouter::registerHandler(handler));
}

bool Messaging::unregisterHandler(
   MessageHandler* handler)
{
   return (MessageRouter::unregisterHandler(handler));
}

bool Messaging::subscribe(
   MessageHandler* handler,
   Topic topic)
{
   return (MessageRouter::subscribe(handler, topic));
}

bool Messaging::unsubscribe(
   MessageHandler* handler,
   Topic topic)
{
   return (MessageRouter::unsubscribe(handler, topic));
}

MessagePtr Messaging::newMessage()
{
   return (MessagePool::newMessage());
}

MessagePtr Messaging::copyMessage(
   MessagePtr copyMessage)
{
   return (MessagePool::copyMessage(copyMessage));
}

void Messaging::freeMessage(
   MessagePtr message)
{
  MessagePool::freeMessage(message);
}

bool Messaging::send(
   MessagePtr message)
{
   return (MessageRouter::send(message));
}

bool Messaging::publish(
   MessagePtr message)
{
   return (MessageRouter::publish(message));
}
