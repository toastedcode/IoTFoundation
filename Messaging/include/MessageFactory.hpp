// *****************************************************************************
// *****************************************************************************
// MessageFactory.hpp
//
// Author: Jason Tost
// Date:   6.3.2016
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "Message.hpp"

class MessageFactory
{

public:

   template <typename T>
   static void allocate(
      const int& numberOfMessages)
   {
      // Destroy any existing pool.
      if (messagePool != 0)
      {
         delete [] messagePool;
         MessageFactory::numberOfMessages = 0;
      }

      // Create the pool.
      messagePool = new MessagePtr[numberOfMessages];
      MessageFactory::numberOfMessages = numberOfMessages;

      // Initialize.
      for (int i = 0; i < numberOfMessages; i++)
      {
         messagePool[i] = new T();
         messagePool[i]->setFree();
      }
   }

   static MessagePtr newMessage();

   static MessagePtr newMessage(
      MessagePtr message);

   static int poolSize();

   static int freeSize();

private:

   static MessagePtr getFreeMessage();

   static MessagePtr* messagePool;

   static int numberOfMessages;
};

inline int MessageFactory::poolSize()
{
   return (numberOfMessages);
}
