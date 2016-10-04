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

   virtual Address getSource() const;

   virtual void setSource(
         const Address& source);

   virtual Address getDestination() const;

   virtual void setDestination(
         const Address& destination);

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
   return (getString("message_id"));
}

inline void BasicMessage::setMessageId(
   const MessageId& messageId)
{
   set("message_id", messageId);
}

inline Address BasicMessage::getSource() const
{
   return (Address(getString("source")));
}

inline void BasicMessage::setSource(
      const Address& source)
{
   set("source", source.toString());
}

inline Address BasicMessage::getDestination() const
{
   return (Address(getString("destination")));
}

inline void BasicMessage::setDestination(
      const Address& destination)
{
   set("destination", destination.toString());
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

inline char BasicMessage::getChar(ParameterName name) const
{
   String value = "";
   return (((value = parameters.get(name)->value) != 0) ? value.charAt(0) : 0);
}

inline double BasicMessage::getDouble(ParameterName name) const
{
   //String value = "";
   //return (((value = parameters.get(name)) != 0) ? value.toDouble() : 0);
   double d = 0;
   return (d);
}

inline float BasicMessage::getFloat(ParameterName name) const
{
   String value = "";
   return (((value = parameters.get(name)->value) != 0) ? value.toFloat() : 0);
}

inline int BasicMessage::getInt(ParameterName name) const
{
   String value = "";
   return (((value = parameters.get(name)->value) != 0) ? value.toInt() : 0);
}

inline String BasicMessage::getString(ParameterName name) const
{
   String value = "";
   return (((value = parameters.get(name)->value) != 0) ? value : "");
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
