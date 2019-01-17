// *****************************************************************************
// *****************************************************************************
// Esp8266Board.hpp
//
// Author: Jason Tost
// Date:   10.17.2016
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "BoardFactory.hpp"
#include "WifiBoard.hpp"

class Esp8266Board : public WifiBoard
{

public:

   // Constructor.
   Esp8266Board();

   // Destructor.
   virtual ~Esp8266Board();

   // **************************************************************************
   // Board operations.

   virtual String getBoardName();

   virtual void pinMode(
      const int& pin,
      const int& mode);

   virtual int analogRead(
      const int& pin);

   virtual void analogWrite(
      const int& pin,
      const int& value);

   virtual int digitalRead(
      const int& pin);

   virtual void digitalWrite(
      const int& pin,
      const int& value);

   virtual void reset();

   virtual void lightSleep(
      const long& milliseconds);

   virtual void deepSleep(
      const long& milliseconds);

   virtual unsigned long systemTime() const;

   // Returns the amount of free memory on the heap, in bytes.
   virtual unsigned long getFreeHeap() const;

   // **************************************************************************
   // WifiBoard operations.

   // This operation retrieves the MAC address of the ESP8266.
   virtual void getMacAddress(
      unsigned char macAddress[6]) const;

   // This operation retrieves the current IP address (if connected) of the ESP8266.
   virtual String getIpAddress() const;

   // This operation attempts to connect to the specified Wifi network using the specified SSID and password.
   // True is returned if the operation was successful; false otherwise.
   // Note: This operation blocks while attempting to make the connection.
   virtual bool connectWifi(
      // The SSID to use in connecting.
      const String& ssid,
      // The password to use in connecting.
      const String& password,
      // A time (in seconds) to attempt to connect.
      const int& connectionTimeout = 30);

   // Disconnect the device from the Wifi network.
   virtual bool disconnectWifi();

   // This operation return true if the ESP8266 is connected to a Wifi network.
   virtual bool isConnected() const;

   // This operation attempts to create a Wifi access point.
   // True is returned if the operation was successful; false otherwise.
   // Note: This operation blocks while attempting to make the AP.
   virtual bool startAccessPoint(
      // The SSID to use in connecting.
      const String& ssid,
      // The password to use in connecting.
      const String& password);

   // This operation stops any currently started Wifi access point.
   // True is returned if the operation was successful; false otherwise.
   virtual bool stopAccessPoint();
};

REGISTER_BOARD(Esp8266Board, Esp8266Board)
