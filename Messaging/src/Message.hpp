// *****************************************************************************
// *****************************************************************************
// Message.hpp
//
// Author: Jason Tost
// Date:   5.25.2016
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "Dictionary.hpp"
#include "MessagingDefs.hpp"

class Message : public Dictionary
{

public:

   Message();

   Message(
      const MessageId& messageId);

   virtual ~Message();

   // Intializes a message for use/reuse.
   virtual void initialize();

   // Intializes a message from another message.
   virtual void initialize(
      const Message& message);

   // This operation retrieves the message id.
   virtual MessageId getMessageId() const;

   // This operation retrieves the message id.
   virtual void setMessageId(
      // The message id.
      const MessageId& messageId);

   // The operation gets the source handler.
   virtual String getSource() const;

   // The operation sets the source handler.
   virtual void setSource(
      // The source message handler.
      const String& id);

   // The operation gets the destination handler.
   virtual String getDestination() const;

   // The operation sets the destination handler.
   virtual void setDestination(
      // The destination message handler.
      const String& id);

   // This operation gets the topic.
   virtual Topic getTopic() const;

   // This operation sets the topic.
   virtual void setTopic(
      // The id of the destination message handler.
      const Topic& topic);

   virtual bool isFree() const;

   virtual void setFree();

   virtual void setInUse();

private:

   bool inUse;
};

typedef Message* MessagePtr;
