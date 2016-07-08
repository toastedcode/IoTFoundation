// *****************************************************************************
// *****************************************************************************
// DynamicMessageQueue.hpp
//
// Author: Jason Tost
// Date:   5.25.2016
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include <list>

#include "Message.hpp"
#include "MessageQueue.hpp"

class DynamicMessageQueue : public MessageQueue
{

public:

   // Constructor.
   DynamicMessageQueue();

   // Destructor.
   virtual ~DynamicMessageQueue();

   // Adds a message to the queue.
   virtual bool enqueue(
      // A pointer to the message to be pushed onto the queue.
      MessagePtr message);

   // Retrieves the next next message in the queue.
   virtual MessagePtr dequeue();

   // Removes all messages from the queue.
   virtual void purge();

   // Returns the number of messages in the queue.
   virtual int size() const;

private:

   std::list<MessagePtr> messageQueue;
};

inline DynamicMessageQueue::DynamicMessageQueue()
{
   // Nothing to do here.
}

inline DynamicMessageQueue::~DynamicMessageQueue()
{
   // Nothing to do here.
}

inline bool DynamicMessageQueue::enqueue(
   MessagePtr message)
{
   messageQueue.push_back(message);

   return (true);
}

inline MessagePtr DynamicMessageQueue::dequeue()
{
   MessagePtr message = NULL;

   if (messageQueue.size() > 0)
   {
      message = messageQueue.front();
      messageQueue.pop_front();
   }

   return (message);
}

inline void DynamicMessageQueue::purge()
{
   messageQueue.clear();
}

inline int DynamicMessageQueue::size() const
{
   return (messageQueue.size());
}
