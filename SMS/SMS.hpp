#pragma once

#include "Arduino.h"

class SMS
{

public:

   static void setup(
      const String& host,
      const int& port,
      const String& twilioAccountSid,
      const String& twilioAuthToken,
      const String& twilioFingerprint,
      const String& twilioPhoneNumber);

   static bool sendSMS(
      const String& phoneNumber,
      const String& body);

private:

   static String host;

   static int port;

   static String twilioAccountSid;

   static String twilioAuthToken;

   static String twilioFingerprint;

   static String twilioPhoneNumber;
};
