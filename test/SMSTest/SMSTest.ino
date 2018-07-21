#include <Board.h>
#include <Logger.h>
#include <SMS.h>

void setup()
{
   Serial.begin(9600);
   Logger::setLogger(new SerialLogger());

   Logger::logDebug("\n\n********** SMS Test **********\n\n");

   Board::setBoard(new Esp8266Board());

   WifiBoard::getBoard()->connectWifi("compunetix-guest", "compunetix");

   SMS::setup(
      "api.twilio.com",  // host
      443,               // port
      "AC47bd79771c6965a92b58d94440e8fa59",  // account sid
      "e97eb2e67fee5d1a6f88a3f66dde0fab",    // auth token
      "REDACTED",        // api.twilio.com SHA1 fingerprint, this one was valid as of May 2018.
      "+14123243446");   // from phone number

   SMS::sendSMS("+17247572815", "I bless the rains down in Africa.");
}

void loop()
{
}
