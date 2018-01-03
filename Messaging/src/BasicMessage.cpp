#include "BasicMessage.hpp"

#include "../../STL/List.hpp"

BasicMessage::BasicMessage() :
   inUse(false)
{
   parameters = new LinkedList<Parameter>();
}

BasicMessage::BasicMessage(
   const MessageId& messageId)
{
   parameters = new LinkedList<Parameter>();
   setMessageId(messageId);
}

BasicMessage::~BasicMessage()
{
   delete (parameters);
}

inline void BasicMessage::initialize()
{
   parameters->clear();
}

inline void BasicMessage::initialize(
   const Message& copyMessage)
{
   initialize();

   const List<Parameter>& copyParameters = copyMessage.getParameters();

   for (List<Parameter>::Iterator it = copyParameters.begin(); it != copyParameters.end(); it++)
   {
      setParameter(*it);
   }
}

inline MessageId BasicMessage::getMessageId() const
{
   return (getString(FPSTR(MESSAGE_ID)));
}

inline void BasicMessage::setMessageId(
   const MessageId& messageId)
{
   set(FPSTR(MESSAGE_ID), messageId);
}

inline String BasicMessage::getSource() const
{
   return (getString(FPSTR(SOURCE)));
}

inline void BasicMessage::setSource(
      const String& source)
{
   set(FPSTR(SOURCE), source);
}

inline String BasicMessage::getDestination() const
{
   return (getString(FPSTR(DESTINATION)));
}

inline void BasicMessage::setDestination(
      const String& destination)
{
   set(FPSTR(DESTINATION), destination);
}

inline Topic BasicMessage::getTopic() const
{
   return (getString(FPSTR(TOPIC)));
}

inline void BasicMessage::setTopic(
   const Topic& topic)
{
   set(FPSTR(TOPIC), topic);
}

inline bool BasicMessage::isFree() const
{
   return (!inUse);
}

inline bool BasicMessage::setFree()
{
   inUse = false;
   return (true);
}

inline bool BasicMessage::setInUse()
{
   inUse = true;
   return (true);
}

bool BasicMessage::getBool(const String& name) const
{
   bool value = false;

   const Parameter* parameter = findParameter(name);
   if (parameter)
   {
      value = parameter->getBoolValue();
   }

   return (value);
}

inline double BasicMessage::getDouble(const String& name) const
{
   double value = 0;

   const Parameter* parameter = findParameter(name);
   if (parameter)
   {
      value = parameter->getDoubleValue();
   }

   return (value);
}

inline float BasicMessage::getFloat(const String& name) const
{
   float value = 0.0F;

   const Parameter* parameter = findParameter(name);
   if (parameter)
   {
      value = parameter->getFloatValue();
   }

   return (value);
}

inline int BasicMessage::getInt(const String& name) const
{
   int value = 0;

   const Parameter* parameter = findParameter(name);
   if (parameter)
   {
      value = parameter->getIntValue();
   }

   return (value);
}

inline String BasicMessage::getString(const String& name) const
{
   String value = "";

   const Parameter* parameter = findParameter(name);
   if (parameter)
   {
      value = parameter->getStringValue();
   }

   return (value);
}

inline void BasicMessage::set(const String& name, bool value)
{
   setParameter(Parameter(name, value));
};

inline void BasicMessage::set(const String& name, double value)
{
   setParameter(Parameter(name, value));
};

inline void BasicMessage::set(const String& name, float value)
{
   setParameter(Parameter(name, value));
};

inline void BasicMessage::set(const String& name, int value)
{
   setParameter(Parameter(name, value));
};

inline void BasicMessage::set(const String& name, char* value)
{
   setParameter(Parameter(name, String(value)));
};

inline void BasicMessage::set(const String& name, const String& value)
{
   setParameter(Parameter(name, value));
};

inline bool BasicMessage::isSet(const String& name) const
{
   return ((name != "") && findParameter(name) != 0);
}

Parameter BasicMessage::getParameter(const String& name) const
{
   return (*(findParameter(name)));
}

const List<Parameter>& BasicMessage::getParameters() const
{
   return (*parameters);
}

bool BasicMessage::setParameter(
   const Parameter& parameter)
{
   bool success = false;

   Parameter* foundParameter = findParameter(parameter.getName());

   if (!foundParameter)
   {
      parameters->add(parameter);
   }
   else
   {
      *foundParameter = parameter;
   }

   return (true);
}

void BasicMessage::clearParameter(
   const String& name)
{
   // TODO: Implment using erase().

   const Parameter* parameter = findParameter(name);
   if (parameter)
   {
      parameters->remove(*parameter);
   }
}

// *****************************************************************************
//                                Private

Parameter* BasicMessage::findParameter(
   const String& name) const
{
   Parameter* parameter = 0;

   for (List<Parameter>::Iterator it = parameters->begin(); it != parameters->end(); it++)
   {
      if (it->getName() == name)
      {
         parameter = (&(*it));
         break;
      }
   }

   return (parameter);
}
