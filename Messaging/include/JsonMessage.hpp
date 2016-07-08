#include "ArduinoJson.h"

class JsonMessage : public Message
{

public:

   // Constructor.
   JsonMessage();

   // Constructor.
   JsonMessage(
      MessageId messageId);

   // Destructor.
   virtual ~JsonMessage();

   // This operation retrieves the message id.
   virtual MessageId getMessageId() const;

   // This operation retrieves the message id.
   virtual void setMessageId(
      // The message id.
      const MessageId& messageId);

   // The operation gets the destination handler.
   virtual HandlerId getDestination() const;

   // The operation sets the destination handler.
   virtual void setDestination(
      // The id of the destination message handler.
      const HandlerId& id);

   // This operation gets the topic.
   virtual Topic getTopic() const;

   // This operation sets the topic.
   virtual void setTopic(
      // The id of the destination message handler.
      const Topic& topic);

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

private:

   StaticJsonBuffer<200> jsonBuffer;

   JsonObject* root;
};


inline MessageId JsonMessage::getMessageId() const
{
   return (getString("message_id"));
}


inline void JsonMessage::setMessageId(
   const MessageId& messageId)
{
   set("message_id", messageId);
}


inline HandlerId JsonMessage::getDestination() const
{
   return (getString("destination"));
}

inline void JsonMessage::setDestination(
   const HandlerId& id)
{
   set("destination", id);
}

inline Topic JsonMessage::getTopic() const
{
   return (getString("topic"));
}

inline void JsonMessage::setTopic(
   const Topic& topic)
{
   set("topic", topic);
}
