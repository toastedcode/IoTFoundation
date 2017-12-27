#include "BasicMessage.hpp"
#include "Esp8266Board.hpp"
#include "Logger.h"
#include "Messaging.h"
#include "Timer.h"

class MyMessageHandler : public MessageHandler, public TimerListener
{
public:

   MyMessageHandler(const String& id) : id(id) {}

   virtual String getId() const
   {
      return (id);
   }

   virtual bool queueMessage(
      MessagePtr message)
   {
      Logger::logDebug("%s: Got %s from %s.", id.c_str(), message->getMessageId().c_str(), message->getSource().c_str());
      message->setFree();
      return (true);
   }

   virtual void timeout(
      Timer* timer)
   {
      Logger::logDebug("Send ...");
      
      Message* message = Messaging::newMessage();

      if (message)
      {
        message->setMessageId("ping");
        message->setSource(id);
        message->setDestination("receiver");
  
        Messaging::send(message);
      }
      else
      {
         Logger::logWarning("Failed to get new message...");
      }
   }

   String id;
};

MyMessageHandler sender("sender");
MyMessageHandler receiver("receiver");

void setup()
{
   Serial.begin(9600);
   Logger::setLogger(new SerialLogger());

   Board::setBoard(new Esp8266Board());
   
   Messaging::setup<BasicMessage>(10);

   Messaging::registerHandler(&sender);
   Messaging::registerHandler(&receiver);

   Timer::setup(1);

   Timer* timer = Timer::newTimer(
    "myTimer",
    500,
    Timer::PERIODIC,
    &sender);

    timer->start();
}

void loop()
{
   Timer::loop();  
}
