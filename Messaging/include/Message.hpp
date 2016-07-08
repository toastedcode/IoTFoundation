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

#include "Address.hpp"
#include "MessagingDefs.hpp"
#include "SmartPointer.hpp"

class Message
{

public:

   // Intializes a message for use/reuse.
   virtual void initialize() = 0;

   // Intializes a message from another message.
   virtual void initialize(
      const Message& message) = 0;

   // This operation retrieves the message id.
   virtual MessageId getMessageId() const = 0;

   // This operation retrieves the message id.
   virtual void setMessageId(
      // The message id.
      const MessageId& messageId) = 0;

   // The operation gets the source handler address.
   virtual Address getSource() const = 0;

   // The operation sets the source handler address.
   virtual void setSource(
      // The address the source message handler.
      const Address& id) = 0;

   // The operation gets the destination handler address.
   virtual Address getDestination() const = 0;

   // The operation sets the destination handler.
   virtual void setDestination(
      // The address the destination message handler.
      const Address& id) = 0;

   // This operation gets the topic.
   virtual Topic getTopic() const = 0;

   // This operation sets the topic.
   virtual void setTopic(
      // The id of the destination message handler.
      const Topic& topic) = 0;

   virtual bool isFree() const = 0;

   virtual bool setFree() = 0;

   virtual bool setInUse() = 0;

   // Operations for getting message parameters.
   virtual bool getBool(ParameterName name) const = 0;
   virtual char getChar(ParameterName name) const = 0;
   virtual double getDouble(ParameterName name) const = 0;
   virtual float getFloat(ParameterName name) const = 0;
   virtual int getInt(ParameterName name) const = 0;
   virtual String getString(ParameterName name) const = 0;

   // Operations for setting message parameters.
   virtual void set(ParameterName name, bool value) = 0;
   virtual void set(ParameterName name, char value) = 0;
   virtual void set(ParameterName name, double value) = 0;
   virtual void set(ParameterName name, float value) = 0;
   virtual void set(ParameterName name, int value) = 0;
   virtual void set(ParameterName name, char* value) = 0;
   virtual void set(ParameterName name, String value) = 0;

   // Returns true if the message has the specified parameter set.
   virtual bool isSet(
      // The name of the parameter to evaluate.
      ParameterName name) const = 0;

   // Serializes the message to a string.
   virtual String serialize() const = 0;

   // Parses the message from a string.
   virtual bool parse(
      const String& messageString) = 0;
};

typedef Message* MessagePtr;
