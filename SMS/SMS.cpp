#include "SMS.hpp"
#include "TwilioProtocol.hpp"
//#include "WiFiClientSecure.h"
#include "ESP8266WiFi.h"

String SMS::host;

int SMS::port;

String SMS::twilioAccountSid;

String SMS::twilioAuthToken;

String SMS::twilioFingerprint;

String SMS::twilioPhoneNumber;

void SMS::setup(
   const String& host,
   const int& port,
   const String& twilioAccountSid,
   const String& twilioAuthToken,
   const String& twilioFingerprint,
   const String& twilioPhoneNumber)
{
   SMS::host = host;
   SMS::port = port;
   SMS::twilioAccountSid = twilioAccountSid;
   SMS::twilioAuthToken = twilioAuthToken;
   SMS::twilioFingerprint = twilioFingerprint;
   SMS::twilioPhoneNumber = twilioPhoneNumber;
}

bool SMS::sendSMS(
   const String& phoneNumber,
   const String& body)
{
   bool isSuccess = false;

   //static WiFiClientSecure client;
   static WiFiClient client;

   static Message message;

   static TwilioProtocol protocol;

   // Check the body is less than 1600 characters in length.
   // https://support.twilio.com/hc/en-us/articles/223181508-Does-Twilio-support-concatenated-SMS-messages-or-messages-over-160-characters-
   // Note: this is only checking ASCII length, not UCS-2 encoding.
   if (body.length() > 1600)
   {
      Logger::logWarning(F("SMS message body must be 1600 or fewer characters."));
   }
   else if (!client.connect(host.c_str(), port))
   {
      Logger::logWarning(F("Failed to connect to host %s:%d."), host.c_str(), port);
   }
   // TODO: Figure out certificate validation.
   /*
   else if (!client.verify(fingerprint.c_str(), host.c_str()))
   {
      Logger::logWarning("Could not verify host %s:%d certificate.", host.c_str(), port);
   }
   */
   else
   {
      message.initialize();

      // Package Twilio parameters in the protocol.
      TwilioProtocol::setHost(&message, host);
      TwilioProtocol::setAccountSid(&message, twilioAccountSid);
      TwilioProtocol::setAuthToken(&message, twilioAuthToken);
      TwilioProtocol::setFromNumber(&message, twilioPhoneNumber);
      TwilioProtocol::setToNumber(&message, phoneNumber);
      TwilioProtocol::setBody(&message, body);

      String serializedMessage = protocol.serialize(&message);

      // Send SMS message.
      client.println(serializedMessage);

      // Read response.
      while (client.connected())
      {
         while (client.available())
         {
            String serializedMessage = client.readStringUntil('\n');

            // For now, just log response.
            // TODO: Parse and handle failures.
            Logger::logDebug(F("SMS reponse: %s"), serializedMessage.c_str());
         }
      }

      isSuccess = true;
   }

   return (isSuccess);
}
