//#include "base64.h"
#include "TwilioProtocol.hpp"
#include "url_coding.hpp"
// Note: Must include Arduino.h (via TwilioProtocol.hpp) because base64.h does not define String.
#include "base64.h"

bool TwilioProtocol::parse(
   const String& messageString,
   MessagePtr message)
{
   // TODO.
   return (0);
}

String TwilioProtocol::serialize(
   MessagePtr message) const
{
   String serializedMessage = "";

   String postData = "To=" + urlencode(getToNumber(message)) +
                     "&From=" + urlencode(getFromNumber(message)) +
                     "&Body=" + getBody(message);

   // Attempt to send an SMS or MMS, depending on picture URL
   String urlImage = getUrlImage(message);
   if (urlImage != "")
   {
      String encoded_image = urlencode(getUrlImage(message));
      postData += "&MediaUrl=" + encoded_image;
   }

   // Construct auth header.
   String authHeader = getAuthHeader(getAccountSid(message), getAuthToken(message));

   serializedMessage = "POST /2010-04-01/Accounts/" +
                       getAccountSid(message) + "/Messages HTTP/1.1\r\n" +
                       authHeader + "\r\n" + "Host: " + getHost(message) + "\r\n" +
                       "Cache-control: no-cache\r\n" +
                       "User-Agent: ESP8266 Twilio Example\r\n" +
                       "Content-Type: " +
                       "application/x-www-form-urlencoded\r\n" +
                       "Content-Length: " + postData.length() +"\r\n" +
                       "Connection: close\r\n" +
                       "\r\n" + postData + "\r\n";


   return (serializedMessage);
}

String TwilioProtocol::getAccountSid(
   MessagePtr message)
{
   return (message->getString(F("accountSid")));
}

void TwilioProtocol::setAccountSid(
   MessagePtr message,
   const String& accountSid)
{
   message->set(F("accountSid"), accountSid);
}

String TwilioProtocol::getAuthToken(
   MessagePtr message)
{
   return (message->getString(F("authToken")));
}

void TwilioProtocol::setAuthToken(
   MessagePtr message,
   const String& authToken)
{
   message->set(F("authToken"), authToken);
}

String TwilioProtocol::getHost(
   MessagePtr message)
{
   return (message->getString(F("host")));
}

void TwilioProtocol::setHost(
   MessagePtr message,
   const String& host)
{
   message->set(F("host"), host);
}

String TwilioProtocol::getUrlImage(
   MessagePtr message)
{
   return (message->getString(F("urlImage")));
}

void TwilioProtocol::setUrlImage(
   MessagePtr message,
   const String& urlImage)
{
   message->set(F("urlImage"), urlImage);
}


String TwilioProtocol::getToNumber(
   MessagePtr message)
{
   return (message->getString(F("toNumber")));
}

void TwilioProtocol::setToNumber(
   MessagePtr message,
   const String& phoneNumber)
{
   message->set(F("toNumber"), phoneNumber);
}

String TwilioProtocol::getFromNumber(
   MessagePtr message)
{
   return (message->getString(F("fromNumber")));
}

void TwilioProtocol::setFromNumber(
   MessagePtr message,
   const String& phoneNumber)
{
   message->set(F("fromNumber"), phoneNumber);
}

String TwilioProtocol::getBody(
   MessagePtr message)
{
   return (message->getString(F("body")));
}

void TwilioProtocol::setBody(
   MessagePtr message,
   const String& body)
{
   message->set(F("body"), body);
}

String TwilioProtocol::getAuthHeader(
   const String& user,
   const String& password)
{
   size_t toencodeLen = user.length() + password.length() + 2;
   char toencode[toencodeLen];
   memset(toencode, 0, toencodeLen);
   snprintf(
      toencode,
      toencodeLen,
      "%s:%s",
      user.c_str(),
      password.c_str()
   );

   String encoded = base64::encode((uint8_t*)toencode, toencodeLen-1);
   String encoded_string = String(encoded);
   int i = 0;

   // Strip newlines (after every 72 characters in spec)
   while (i < encoded_string.length())
   {
      i = encoded_string.indexOf('\n', i);
      if (i == -1)
      {
         break;
      }
      encoded_string.remove(i, 1);
   }

   return "Authorization: Basic " + encoded_string;
}
