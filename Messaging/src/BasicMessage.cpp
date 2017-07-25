#include "BasicMessage.hpp"

BasicMessage::BasicMessage() :
   inUse(false)
{
   // Nothing to do here.
}

BasicMessage::BasicMessage(
   const MessageId& messageId)
{
   setMessageId(messageId);
}

BasicMessage::~BasicMessage()
{
   // Nothing to do here.
}

inline void BasicMessage::initialize()
{
   for (int i = 0; i < MAX_PARAMETERS; i++)
   {
      parameters[i].initialize();
   }
}

inline void BasicMessage::initialize(
   const Message& copyMessage)
{
   static int count = 0;
   Parameter copyParameters[MAX_PARAMETERS];

   copyMessage.getParameters(copyParameters, count);

   for (int i = 0; i < count; i++)
   {
      setParameter(copyParameters[i]);
   }
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

bool BasicMessage::getBool(const String& name) const
{
   bool value = false;

   const Parameter* parameter = findParameter(name.c_str());
   if (parameter)
   {
      value = parameter->getBoolValue();
   }

   return (value);
}

inline double BasicMessage::getDouble(const String& name) const
{
   double value = 0;

   const Parameter* parameter = findParameter(name.c_str());
   if (parameter)
   {
      value = parameter->getDoubleValue();
   }

   return (value);
}

inline float BasicMessage::getFloat(const String& name) const
{
   float value = 0.0F;

   const Parameter* parameter = findParameter(name.c_str());
   if (parameter)
   {
      value = parameter->getFloatValue();
   }

   return (value);
}

inline int BasicMessage::getInt(const String& name) const
{
   int value = 0;

   const Parameter* parameter = findParameter(name.c_str());
   if (parameter)
   {
      value = parameter->getIntValue();
   }

   return (value);
}

inline String BasicMessage::getString(const String& name) const
{
   String value = "";

   const Parameter* parameter = findParameter(name.c_str());
   if (parameter)
   {
      value = String(parameter->getStringValue());
   }

   return (value);
}

inline void BasicMessage::set(const String& name, bool value)
{
   setParameter(Parameter(name.c_str(), value));
};

inline void BasicMessage::set(const String& name, double value)
{
   setParameter(Parameter(name.c_str(), value));
};

inline void BasicMessage::set(const String& name, float value)
{
   setParameter(Parameter(name.c_str(), value));
};

inline void BasicMessage::set(const String& name, int value)
{
   setParameter(Parameter(name.c_str(), value));
};

inline void BasicMessage::set(const String& name, char* value)
{
   setParameter(Parameter(name.c_str(), value));
};

inline void BasicMessage::set(const String& name, String value)
{
   setParameter(Parameter(name.c_str(), value.c_str()));
};

inline bool BasicMessage::isSet(const String& name) const
{
   return ((name != "") && findParameter(name.c_str()) != 0);
}

bool BasicMessage::setParameter(
   const Parameter& parameter)
{
   bool success = false;

   for (int i = 0; i < MAX_PARAMETERS; i++)
   {
      // Look for an empty slot.
      if (strnlen(parameters[i].getName(), sizeof(Parameter::ParameterName)) == 0)
      {
         parameters[i] = parameter;
         success = true;
         break;
      }
   }

   return (success);
}


void BasicMessage::getParameters(
   Parameter parameters[],
   int& count) const
{
   for (int i = 0; i < MAX_PARAMETERS; i++)
   {
      if (strnlen(this->parameters[i].getName(), Parameter::PARAMETER_NAME_SIZE) != 0)
      {
         parameters[i] = this->parameters[i];
         count++;
      }
   }
}

// *****************************************************************************
//                                Private

const Parameter* BasicMessage::findParameter(
   const char* name) const
{
   const Parameter* parameter;

   for (int i = 0; i < MAX_PARAMETERS; i++)
   {
      if (strncmp(name, parameters[i].getName(), sizeof(Parameter::ParameterName)) == 0)
      {
         parameter = &(parameters[i]);
         break;
      }
   }

   return (parameter);
}

Parameter* BasicMessage::getParameter(
   const char* name)
{
   Parameter* parameter;

   for (int i = 0; i < MAX_PARAMETERS; i++)
   {
      if (strncmp(name, parameters[i].getName(), sizeof(Parameter::ParameterName)) == 0)
      {
         parameter = &(parameters[i]);
         break;
      }
   }

   return (parameter);
}

void BasicMessage::clearParameter(
   const char* name)
{
   Parameter* parameter = getParameter(name);
   if (parameter)
   {
      parameter->initialize();
   }
}
