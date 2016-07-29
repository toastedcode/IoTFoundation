// *****************************************************************************
// *****************************************************************************
// MessageQueue.hpp
//
// Author: Jason Tost
// Date:   5.25.2016
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "Message.hpp"

class MessageQueue
{

public:

   // Adds a message to the queue.
   virtual bool enqueue(
      // A pointer to the message to be pushed onto the queue.
      MessagePtr message) = 0;

   // Retrieves the next next message in the queue.
   virtual MessagePtr dequeue() = 0;

   // Removes all messages from the queue.
   virtual void purge() = 0;

   // Returns the number of messages in the queue.
   virtual int size() const = 0;
};
