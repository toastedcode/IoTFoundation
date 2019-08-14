#include "Arduino.h"
#include "EspBoard.hpp"
#include "EspWifi.hpp"
#include "Logger.hpp"

EspBoard::EspBoard()
{
}

EspBoard::~EspBoard()
{
}

// **************************************************************************
// Board operations

void EspBoard::pinMode(
   const int& pin,
   const int& mode)
{
   ::pinMode(pin, mode);
}

int EspBoard::analogRead(
   const int& pin)
{
   return (::analogRead(pin));
}

int EspBoard::digitalRead(
   const int& pin)
{
   return (::digitalRead(pin));
}

void EspBoard::digitalWrite(
   const int& pin,
   const int& value)
{
   return (::digitalWrite(pin, value));
}

void EspBoard::reset()
{
   Logger::logInfo("Resetting board ...");
   ESP.restart();
}

void EspBoard::lightSleep(
   const long& milliseconds)
{
   // TODO
}

void EspBoard::deepSleep(
   const long& milliseconds)
{
   // TODO
}

unsigned long EspBoard::systemTime() const
{
   return (millis());
}

unsigned long EspBoard::getFreeHeap() const
{
   return (ESP.getFreeHeap());
}

// **************************************************************************
// WifiBoard operations

void EspBoard::getMacAddress(
   unsigned char macAddress[6]) const
{
   WiFi.macAddress(macAddress);
}

String EspBoard::getIpAddress() const
{
   return (WiFi.localIP().toString());
}


bool EspBoard::connectWifi(
   const String& ssid,
   const String& password,
   const int& connectionTimeout)
{
   Logger::logDebug(F("Connecting to Wifi network %s ..."), ssid.c_str());

   if (WiFi.getMode() == WIFI_AP)
   {
      WiFi.mode(WIFI_AP_STA);
   }
   else
   {
      WiFi.mode(WIFI_STA);
   }

   WiFi.begin(ssid.c_str(), password.c_str());

   int secondsToConnect = 0;

   // Wait until the connection is made, or until we timeout.
   while ((isConnected() == false) &&
          (secondsToConnect < connectionTimeout))
   {
      delay(1000);
      secondsToConnect++;
      Logger::logDebug(F("trying ..."));
   }

   if (isConnected())
   {
      Logger::logDebug(F("Success!  Connected at %s"), getIpAddress().c_str());
   }
   else
   {
      Logger::logDebug(F("Failure!  Could not connect to %s"), ssid.c_str());
   }

   return (isConnected());
}

bool EspBoard::disconnectWifi()
{
   if ((WiFi.getMode() == WIFI_STA) ||
       (WiFi.getMode() == WIFI_AP_STA))
   {
      Logger::logDebug(F("Disconnected from Wifi network."));

      WiFi.disconnect();

      if (WiFi.getMode() == WIFI_AP_STA)
      {
         WiFi.mode(WIFI_AP);
      }
      else
      {
         WiFi.mode(WIFI_OFF);
      }
   }

   return (!isConnected());
}

bool EspBoard::isConnected() const
{
   return (WiFi.status() == WL_CONNECTED);
}

bool EspBoard::startAccessPoint(
   const String& ssid,
   const String& password)
{
   Logger::logDebug(F("Creating wireless network %s."), ssid.c_str());

   if ((WiFi.getMode() == WIFI_AP) ||
       (WiFi.getMode() == WIFI_AP_STA))
   {
      WiFi.mode(WIFI_AP_STA);
   }
   else
   {
      WiFi.mode(WIFI_AP);
   }

   WiFi.softAP(ssid.c_str(), password.c_str());

   return (isConnected());
}

bool EspBoard::stopAccessPoint()
{
   if ((WiFi.getMode() == WIFI_AP) ||
       (WiFi.getMode() == WIFI_AP_STA))
   {
      Logger::logDebug(F("Stopping wireless network %s."), WiFi.SSID().c_str());

      if (WiFi.getMode() == WIFI_AP_STA)
      {
         WiFi.mode(WIFI_STA);
      }
      else
      {
         WiFi.mode(WIFI_OFF);
      }
   }

   return (!isConnected());
}
