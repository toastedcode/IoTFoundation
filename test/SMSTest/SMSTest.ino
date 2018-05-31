#include <Board.h>
#include <Logger.h>
#include <Messaging.h>
#include <SMS.h>

SMSAdapter* sms = 0;

void setup()
{
   Serial.begin(9600);
   Logger::setLogger(new SerialLogger());

   Board::setBoard(new Esp8266Board());

   Messaging::setup(10);

   sms = new SMSAdapter("sms",             // id
                        "api.twilio.com",  // host
                        443,               // port
                        "REDACTED",        // account sid
                        "REDACTED",        // auth token
                        "REDACTED",        // api.twilio.com SHA1 fingerprint, this one was valid as of May 2018.
                        "REDACTED");       // from phone number

   Messaging::registerHandler(sms);

   WifiBoard::getBoard()->connectWifi("REDACTED", "REDACTED");

   sms->sendSMSMessage("+17247572815", "I bless the rains down in Africa.");
}

void loop()
{
  sms->loop(); 
}
