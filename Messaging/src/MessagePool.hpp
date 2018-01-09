#pragma once

#include "Message.hpp"
#include "Pool.hpp"

class MessagePool
{

public:

   static void setup(
      const int& messagePoolSize);

   static MessagePtr newMessage();

   static MessagePtr copyMessage(
      MessagePtr message);

   static void freeMessage(
      MessagePtr message);

private:

   static Pool<Message>* messagePool;
};
