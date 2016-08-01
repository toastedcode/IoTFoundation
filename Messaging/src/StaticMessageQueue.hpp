// *****************************************************************************
// *****************************************************************************
// StaticMessageQueue.hpp
//
// Author: Jason Tost
// Date:   7.8.2016
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "Message.hpp"
#include "MessageQueue.hpp"

class StaticMessageQueue : public MessageQueue
{

public:

   // Constructor.
   StaticMessageQueue(
      const int& size);

   // Destructor.
   virtual ~StaticMessageQueue();

   // Adds a message to the queue.
   virtual bool enqueue(
      // A pointer to the message to be pushed onto the queue.
      MessagePtr message);

   // Retrieves the increment increment message in the queue.
   virtual MessagePtr dequeue();

   // Removes all messages from the queue.
   virtual void purge();

   // Returns the number of messages in the queue.
   virtual int size() const;

private:

   bool full() const;

   bool empty() const;

   void increment(
      int& index) const;

   MessagePtr* messageQueue;

   int queueSize;

   int end;

   int begin;
};

inline StaticMessageQueue::StaticMessageQueue(
   const int& size)
{
   messageQueue = new MessagePtr[size];
   memset(messageQueue, 0, (sizeof(MessagePtr) * size));

   end = 0;
   begin = 0;
   queueSize = size;
}

inline StaticMessageQueue::~StaticMessageQueue()
{
   delete [] messageQueue;
}

inline bool StaticMessageQueue::enqueue(
   MessagePtr message)
{
   bool success = false;

   if (!full())
   {
      messageQueue[end] = message;

      increment(end);

      success = true;
   }

   return (success);
}

inline MessagePtr StaticMessageQueue::dequeue()
{
   MessagePtr message = NULL;

   if (!empty())
   {
      message = messageQueue[begin];
      messageQueue[begin] = NULL;

      increment(begin);
   }

   return (message);
}

inline void StaticMessageQueue::purge()
{
   memset(messageQueue, 0, (sizeof(MessagePtr) * queueSize));
   end = 0;
   begin = 0;
}

inline int StaticMessageQueue::size() const
{
   return (queueSize);
}

inline bool StaticMessageQueue::full() const
{
   return ((end == begin) &&
           (messageQueue[begin] != NULL));
}

inline bool StaticMessageQueue::empty() const
{
   return ((end == begin) &&
           (messageQueue[begin] == NULL));

}

inline void StaticMessageQueue::increment(
   int& index) const
{
   index++;
   if (index >= queueSize)
   {
      index = 0;
   }
}
