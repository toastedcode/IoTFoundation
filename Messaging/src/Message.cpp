#include "Message.hpp"

Message::Message()
{
   // Nothing to do here.
}

Message::Message(
   const MessageId& messageId)
{
   setMessageId(messageId);
}

Message::~Message()
{
   // Nothing to do here.
}

inline void Message::initialize()
{
   clear();
}

inline void Message::initialize(
   const Message& copyMessage)
{
   initialize();

   *this = copyMessage;
}

inline MessageId Message::getMessageId() const
{
   return (getString(FPSTR(MESSAGE_ID)));
}

inline void Message::setMessageId(
   const MessageId& messageId)
{
   set(FPSTR(MESSAGE_ID), messageId);
}

inline String Message::getSource() const
{
   return (getString(FPSTR(SOURCE)));
}

inline void Message::setSource(
      const String& source)
{
   set(FPSTR(SOURCE), source);
}

inline String Message::getDestination() const
{
   return (getString(FPSTR(DESTINATION)));
}

inline void Message::setDestination(
      const String& destination)
{
   set(FPSTR(DESTINATION), destination);
}

inline Topic Message::getTopic() const
{
   return (getString(FPSTR(TOPIC)));
}

inline void Message::setTopic(
   const Topic& topic)
{
   set(FPSTR(TOPIC), topic);
}
