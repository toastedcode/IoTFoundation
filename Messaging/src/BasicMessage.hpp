#pragma once

#include "Map.hpp"
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

   virtual int getParameterCount();

   virtual Parameter getParameter(
      const int& index);

   virtual Parameter getParameter(
      const ParameterName& name);

   virtual void setParameter(
      const Parameter& parameter);

   // Operations for getting message parameters.
   virtual bool getBool(ParameterName name) const;
   virtual char getChar(ParameterName name) const;
   virtual double getDouble(ParameterName name) const;
   virtual float getFloat(ParameterName name) const;
   virtual int getInt(ParameterName name) const;
   virtual String getString(ParameterName name) const;

   // Operations for setting message parameters.
   virtual void set(ParameterName name, bool value);
   virtual void set(ParameterName name, char value);
   virtual void set(ParameterName name, double value);
   virtual void set(ParameterName name, float value);
   virtual void set(ParameterName name, int value);
   virtual void set(ParameterName name, char* value);
   virtual void set(ParameterName name, String value);

   // Returns true if the message has the specified parameter set.
   virtual bool isSet(
      // The name of the parameter to evaluate.
      ParameterName name) const;

private:

   typedef Map<String, Parameter, MAX_PARAMETERS> ParameterMap;

   ParameterMap parameters;

   bool inUse;
};

inline BasicMessage::BasicMessage()
{
   // Nothing to do here.
}

inline BasicMessage::BasicMessage(
   const MessageId& messageId)
{
   set("message_id", messageId);
}

inline BasicMessage::~BasicMessage()
{
   // Nothing to do here.
}

inline void BasicMessage::initialize()
{
   parameters.clear();
}

inline void BasicMessage::initialize(
   const Message& copyMessage)
{
}

inline MessageId BasicMessage::getMessageId() const
{
   return (getString("messageId"));
}

inline void BasicMessage::setMessageId(
   const MessageId& messageId)
{
   set("messageId", messageId);
}

inline String BasicMessage::getSource() const
{
   return (getString("source"));
}

inline void BasicMessage::setSource(
      const String& source)
{
   set("source", source);
}

inline String BasicMessage::getDestination() const
{
   return (getString("destination"));
}

inline void BasicMessage::setDestination(
      const String& destination)
{
   set("destination", destination);
}

inline Topic BasicMessage::getTopic() const
{
   return (getString("topic"));
}

inline void BasicMessage::setTopic(
   const Topic& topic)
{
   set("topic", topic);
}

inline bool BasicMessage::isFree() const
{
   return (!inUse);
}

inline bool BasicMessage::setFree()
{
   inUse = false;
}

inline bool BasicMessage::setInUse()
{
   inUse = true;
}

inline char BasicMessage::getChar(
   ParameterName name) const
{
   char value = 0;

   if ((parameters.isSet(name)) &&
       (parameters.get(name)->value.length() > 0))
   {
      value = parameters.get(name)->value.charAt(0);
   }

   return (value);
}

inline double BasicMessage::getDouble(ParameterName name) const
{
   double value = 0;

   if (parameters.isSet(name))
   {
      // TODO
      //value = parameters.get(name)->value.toDouble();
   }

   return (value);
}

inline float BasicMessage::getFloat(ParameterName name) const
{
   float value = 0;

   if (parameters.isSet(name))
   {
      value = parameters.get(name)->value.toFloat();
   }

   return (value);
}

inline int BasicMessage::getInt(ParameterName name) const
{
   int value = 0;

   if (parameters.isSet(name))
   {
      value = parameters.get(name)->value.toInt();
   }

   return (value);
}

inline String BasicMessage::getString(ParameterName name) const
{
   String value = "";

   if (parameters.isSet(name))
   {
      value = parameters.get(name)->value;
   }

   return (value);
}

inline void BasicMessage::set(ParameterName name, bool value)
{
   parameters.put(name, Parameter(name, String((value == true) ? "true" : "false"), BOOL));
};

inline void BasicMessage::set(ParameterName name, char value)
{
   parameters.put(name, Parameter(name, String(value), CHAR));
};

inline void BasicMessage::set(ParameterName name, double value)
{
   parameters.put(name, Parameter(name, String(value), DOUBLE));
};

inline void BasicMessage::set(ParameterName name, float value)
{
   parameters.put(name, Parameter(name, String(value), FLOAT));
};

inline void BasicMessage::set(ParameterName name, int value)
{
   parameters.put(name, Parameter(name, String(value), INT));
};

inline void BasicMessage::set(ParameterName name, char* value)
{
   parameters.put(name, Parameter(name, String(value), STRING));
};

inline void BasicMessage::set(ParameterName name, String value)
{
   parameters.put(name, Parameter(name, value, STRING));
};

inline bool BasicMessage::isSet(ParameterName name) const
{
   return (parameters.isSet(name));
}
