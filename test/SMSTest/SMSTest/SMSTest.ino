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

   sms = new SMSAdapter("sms",                                                          // id
                        "api.twilio.com",                                               // host
                        443,                                                            // port
                        "AC47bd79771c6965a92b58d94440e8fa59",                           // account sid
                        "e97eb2e67fee5d1a6f88a3f66dde0fab",                             // auth token
                        "‎‎cf c4 40 77 88 75 5f bd 07 0f 88 3f 1c bd 95 3b dd ae 5f 13",  // api.twilio.com SHA1 fingerprint, this one was valid as of May 2018.
                        "+14123243446");                                                // from phone number

   Messaging::registerHandler(sms);

   WifiBoard::getBoard()->connectWifi("TostNet", "t0stn3t5");

   sms->sendSMSMessage("+17247572815", "I bless the rains down in Africa.");
}

void loop()
{
  sms->loop(); 
}
