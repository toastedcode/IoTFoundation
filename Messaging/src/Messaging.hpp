#pragma once

#include "MessageHandler.hpp"
#include "Pool.hpp"

class Messaging
{

public:

   static void setup(
      const int& messagePoolSize);

   static bool registerHandler(
      MessageHandler* handler);

   static bool unregisterHandler(
      MessageHandler* handler);

   static bool subscribe(
      // The handler to be subscribed.
      MessageHandler* handler,
      // The topic to which the handler should be subscribed.
      Topic topic);

   static bool unsubscribe(
      // The handler to be unsubscribed.
      MessageHandler* handler,
      // The topic to which the handler should be unsubscribed.
      Topic topic);

   static MessagePtr newMessage();

   static MessagePtr copyMessage(
      MessagePtr copyMessage);

   static void freeMessage(
      MessagePtr message);

   // This operation sends a message to a single component.
   static bool send(
      // The message to send.
      MessagePtr message);

   // This operation sends a message to a subscribed components.
   static bool publish(
      // The message to send.
      MessagePtr message);
};
