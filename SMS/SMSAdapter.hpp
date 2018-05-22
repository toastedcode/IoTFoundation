// *****************************************************************************
// *****************************************************************************
// SMSAdapter.hpp
//
// Author: Jason Tost
// Date:   5.21.2018
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "Adapter.hpp"
#include "WiFiClientSecure.h"

class SMSAdapter : public Adapter
{

public:

   SMSAdapter(
      const String& id,
      const String& host,
      const int& port,
      const String& twilioAccountSid,
      const String& twilioAuthToken,
      const String& twilioFingerprint,
      const String& twilioPhoneNumber);

   virtual ~SMSAdapter();

   virtual bool sendRemoteMessage(
      MessagePtr message);

   virtual MessagePtr getRemoteMessage();

private:

   WiFiClientSecure client;

   String host;

   int port;

   String twilioAccountSid;

   String twilioAuthToken;

   String twilioFingerprint;

   String twilioPhoneNumber;
};
