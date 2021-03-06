#include "Arduino.h"
#include "Esp8266Board.hpp"
#include "ESP8266WiFi.h"
#include "Logger.hpp"

Esp8266Board::Esp8266Board() {}

Esp8266Board::~Esp8266Board() {}

int Esp8266Board::getChipId()
{
   return (ESP.getChipId());
}

// **************************************************************************
// Board operations

String Esp8266Board::getBoardName()
{
   return (F("ESP8266"));
}

void Esp8266Board::pinMode(
   const int& pin,
   const int& mode)
{
   ::pinMode(pin, mode);
}

int Esp8266Board::analogRead(
   const int& pin)
{
   return (::analogRead(pin));
}

void Esp8266Board::analogWrite(
   const int& pin,
   const int& value)
{
   ::analogWrite(pin, value);
}

int Esp8266Board::digitalRead(
   const int& pin)
{
   return (::digitalRead(pin));
}

void Esp8266Board::digitalWrite(
   const int& pin,
   const int& value)
{
   return (::digitalWrite(pin, value));
}

void Esp8266Board::reset()
{
   Logger::logInfo("Resetting ESP8266 ...");
   ESP.restart();
}

void Esp8266Board::lightSleep(
   const long& milliseconds)
{
   // TODO
}

void Esp8266Board::deepSleep(
   const long& milliseconds)
{
   // TODO
}

unsigned long Esp8266Board::systemTime() const
{
   return (millis());
}

unsigned long Esp8266Board::getFreeHeap() const
{
   return (ESP.getFreeHeap());
}

// **************************************************************************
// WifiBoard operations

void Esp8266Board::getMacAddress(
   unsigned char macAddress[6]) const
{
   WiFi.macAddress(macAddress);
}

String Esp8266Board::getIpAddress() const
{
   return (WiFi.localIP().toString());
}


bool Esp8266Board::connectWifi(
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

bool Esp8266Board::disconnectWifi()
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

bool Esp8266Board::isConnected() const
{
   return (WiFi.status() == WL_CONNECTED);
}

bool Esp8266Board::startAccessPoint(
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

bool Esp8266Board::stopAccessPoint()
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
