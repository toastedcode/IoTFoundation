// *****************************************************************************
// *****************************************************************************
// ESP8266.cpp
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include "ESP8266.h"

#include "../../Logger/src/Logger.h"

Esp8266* Esp8266::instance = 0;

Esp8266::Esp8266()
{
   // Create pins.
   for (int pinId = 1; pinId <= MAX_NUM_PINS; pinId++)
   {
      pins[pinId - 1] = new Pin(pinId);
   }
}

Esp8266::~Esp8266()
{
   // Delete pins.
   for (int pinId = 1; pinId <= MAX_NUM_PINS; pinId++)
   {
      if (pins[pinId - 1])
      {
         delete pins[pinId - 1];
      }
   }
}

String Esp8266::getMacAddress() const
{
   unsigned char macAddress[6];
   WiFi.macAddress(macAddress);

   //return (String(macAddress));
   return ("");
}

IPAddress Esp8266::getIpAddress() const
{
   return (WiFi.localIP());
}

bool Esp8266::connectWifi(
   const int& connectionTimeout)
{
   Logger::logDebug("Connecting to Wifi network %s ...", WiFi.SSID().c_str());

   WiFi.mode(WIFI_STA);
   //WiFi.begin();

   int secondsToConnect = 0;

   // Wait until the connection is made, or until we timeout.
   while ((isConnected() == false) &&
          (secondsToConnect < connectionTimeout))
   {
      delay(1000);
      secondsToConnect++;
      Logger::logDebug("... trying ...");
   }

   if (isConnected())
   {
      Logger::logDebug("Success!  Connected at %s", toString(getIpAddress()).c_str());
   }
   else
   {
      Logger::logDebug("Failure!  Could not connect to %s", WiFi.SSID().c_str());
   }

   return (isConnected());
}

bool Esp8266::connectWifi(
   const String& ssid,
   const String& password,
   const int& connectionTimeout)
{
   Logger::logDebug("Connecting to Wifi network %s ...", ssid.c_str());

   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid.c_str(), password.c_str());

   int secondsToConnect = 0;

   // Wait until the connection is made, or until we timeout.
   while ((isConnected() == false) &&
          (secondsToConnect < connectionTimeout))
   {
      delay(1000);
      secondsToConnect++;
      Logger::logDebug("... trying ...");
   }

   if (isConnected())
   {
      Logger::logDebug("Success!  Connected at %s", toString(getIpAddress()).c_str());
   }
   else
   {
      Logger::logDebug("Failure!  Could not connect to %s", WiFi.SSID().c_str());
   }

   return (isConnected());
}

bool Esp8266::startAccessPoint(
   const String& ssid,
   const String& password)
{
   Logger::logDebug("Creating wireless network %s.", ssid.c_str());

   WiFi.mode(WIFI_AP);
   WiFi.softAP(ssid.c_str(), password.c_str());

   return (isConnected());
}

bool Esp8266::stopAccessPoint()
{
   Logger::logDebug("Stopping wireless network %s.", WiFi.SSID().c_str());

   WiFi.softAPdisconnect();

   return (!isConnected());
}

void Esp8266::reset()
{
   // TODO
}

String Esp8266::toString(
   const IPAddress& ipAddress)
{
   String string = "";

   for (int octet = 0; octet < 4; octet++)
   {
      string += String(ipAddress[octet]);
      if (octet < 3)
      {
         string += ".";
      }
   }

   return (string);
}
