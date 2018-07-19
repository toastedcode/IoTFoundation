#pragma once

#include "Protocol.hpp"

class TwilioProtocol
{

public:

   virtual bool parse(
      const String& messageString,
      MessagePtr message);

   virtual String serialize(
      MessagePtr message) const;

   // **************************************************************************

   static String getAccountSid(
      MessagePtr message);

   static void setAccountSid(
      MessagePtr message,
      const String& accountSid);

   static String getAuthToken(
      MessagePtr message);

   static void setAuthToken(
      MessagePtr message,
      const String& authToken);

   static String getHost(
      MessagePtr message);

   static void setHost(
      MessagePtr message,
      const String& host);

   static String getUrlImage(
      MessagePtr message);

   static void setUrlImage(
      MessagePtr message,
      const String& urlImage);

   static String getToNumber(
      MessagePtr message);

   static void setToNumber(
      MessagePtr message,
      const String& phoneNumber);

   static String getFromNumber(
      MessagePtr message);

   static void setFromNumber(
      MessagePtr message,
      const String& phoneNumber);

   static String getBody(
      MessagePtr message);

   static void setBody(
      MessagePtr message,
      const String& body);

private:

   static String getAuthHeader(
      const String& user,
      const String& password);
};
