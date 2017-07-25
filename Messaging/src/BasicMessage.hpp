#pragma once

#include "Message.hpp"

class BasicMessage : public Message
{

public:

   static const int MAX_PARAMETERS = 10;

   BasicMessage();

   BasicMessage(
      const MessageId& messageId);

   virtual ~BasicMessage();

   virtual void initialize();

   virtual void initialize(
      const Message& copyMessage);

   virtual MessageId getMessageId() const;

   virtual void setMessageId(
      const MessageId& messageId);

   virtual String getSource() const;

   virtual void setSource(
         const String& source);

   virtual String getDestination() const;

   virtual void setDestination(
         const String& destination);

   virtual Topic getTopic() const;

   virtual void setTopic(
      const Topic& topic);

   virtual bool isFree() const;

   virtual bool setFree();

   virtual bool setInUse();

   // Operations for getting message parameters.
   virtual bool getBool(const String& name) const;
   virtual double getDouble(const String& name) const;
   virtual float getFloat(const String& name) const;
   virtual int getInt(const String& name) const;
   virtual String getString(const String& name) const;

   // Operations for setting message parameters.
   virtual void set(const String& name, bool value);
   virtual void set(const String& name, double value);
   virtual void set(const String& name, float value);
   virtual void set(const String& name, int value);
   virtual void set(const String& name, char* value);
   virtual void set(const String& name, String value);

   // Returns true if the message has the specified parameter set.
   virtual bool isSet(
      // The name of the parameter to evaluate.
      const String& name) const;

   virtual bool setParameter(const Parameter& parameter);

   virtual void getParameters(
      Parameter parameters[],
      int& count) const;

private:

   const Parameter* findParameter(
      const char* name) const;

   Parameter* getParameter(
      const char* name);

   void clearParameter(
      const char* name);

   Parameter parameters[MAX_PARAMETERS];

   bool inUse;
};
