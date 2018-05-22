#include "Logger.hpp"
#include "SMSAdapter.hpp"
#include "TwilioProtocol.hpp"

SMSAdapter::SMSAdapter(
   const String& id,
   const String& host,
   const int& port,
   const String& twilioAccountSid,
   const String& twilioAuthToken,
   const String& twilioFingerprint,
   const String& twilioPhoneNumber) :
      Adapter(id, new TwilioProtocol()),
      host(host),
      port(port),
      twilioAccountSid(twilioAccountSid),
      twilioAuthToken(twilioAuthToken),
      twilioFingerprint(twilioFingerprint),
      twilioPhoneNumber(twilioPhoneNumber)
{

}

SMSAdapter::~SMSAdapter()
{

}

bool SMSAdapter::sendRemoteMessage(
   MessagePtr message)
{
   bool isSuccess = false;

   // Check the body is less than 1600 characters in length.
   // https://support.twilio.com/hc/en-us/articles/223181508-Does-Twilio-support-concatenated-SMS-messages-or-messages-over-160-characters-
   // Note: this is only checking ASCII length, not UCS-2 encoding.
   if (message->getString("body").length() > 1600)
   {
      Logger::logWarning("SMS message body must be 1600 or fewer characters.");
   }
   else if (!client.connect(host.c_str(), port))
   {
      Logger::logWarning("Failed to connect to host %s:%d.", host.c_str(), port);
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
      // Package Twilio parameters in the protocol.
      TwilioProtocol::setHost(message, host);
      TwilioProtocol::setAccountSid(message, twilioAccountSid);
      TwilioProtocol::setAuthToken(message, twilioAuthToken);
      TwilioProtocol::setFromNumber(message, twilioPhoneNumber);

      String serializedMessage = protocol->serialize(message);

      client.println(serializedMessage);

      isSuccess = true;
   }

   return true;
}

MessagePtr SMSAdapter::getRemoteMessage()
{
   MessagePtr message = 0;

   while (client && client.available())
   {
      String serializedMessage = client.readStringUntil('\n');

      // For now, just log response.
      // TODO: Parse and handle failures.
      Logger::logDebug("SMS reponse: %s", serializedMessage.c_str());
   }

   return (message);
}
