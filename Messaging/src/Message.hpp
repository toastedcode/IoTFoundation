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

#include "MessagingDefs.hpp"

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

   // The operation gets the source handler.
   virtual String getSource() const = 0;

   // The operation sets the source handler.
   virtual void setSource(
      // The source message handler.
      const String& id) = 0;

   // The operation gets the destination handler.
   virtual String getDestination() const = 0;

   // The operation sets the destination handler.
   virtual void setDestination(
      // The destination message handler.
      const String& id) = 0;

   // This operation gets the topic.
   virtual Topic getTopic() const = 0;

   // This operation sets the topic.
   virtual void setTopic(
      // The id of the destination message handler.
      const Topic& topic) = 0;

   virtual bool isFree() const = 0;

   virtual bool setFree() = 0;

   virtual bool setInUse() = 0;

   virtual int getParameterCount() const = 0;

   virtual Parameter getParameter(
      const int& index) const = 0;

   virtual Parameter getParameter(
      const ParameterName& name) const = 0;

   virtual void setParameter(
      const Parameter& parameter) = 0;

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
};

typedef Message* MessagePtr;
