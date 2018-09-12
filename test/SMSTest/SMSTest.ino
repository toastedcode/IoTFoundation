#include <Board.h>
#include <Logger.h>
#include <SMS.h>

void setup()
{
   Serial.begin(9600);
   Logger::setLogger(new SerialLogger());

   Logger::logDebug("\n\n********** SMS Test **********\n\n");

   Board::setBoard(new Esp8266Board());

   WifiBoard::getBoard()->connectWifi("REDACTED", "REDACTED");

   SMS::setup(
      "api.twilio.com",  // host
      443,               // port
      "REDACTED",  // account sid
      "REDACTED",    // auth token
      "4C FE 00 19 F3 57 89 7B 02 9A A4 AA 2E 7B CB 6E 53 D1 7E AE",   // api.twilio.com SHA1 fingerprint, this one was valid as of 9/12/2018.
      "REDACTED");   // from phone number

   SMS::sendSMS("REDACTED", "I bless the rains down in Africa.");
}

void loop()
{
}
