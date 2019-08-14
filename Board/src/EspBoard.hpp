// *****************************************************************************
// *****************************************************************************
// EspBoard.hpp
//
// Author: Jason Tost
// Date:   8.8.2019
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "WifiBoard.hpp"

class EspBoard : public WifiBoard
{

public:

   // Constructor.
   EspBoard();

   // Destructor.
   virtual ~EspBoard();

   // Not implemented in base class.
   // Note: ESP.getChipId() is not supported in ESP32.
   virtual int getChipId() = 0;

   // **************************************************************************
   // Board operations.

   virtual void pinMode(
      const int& pin,
      const int& mode);

   virtual int analogRead(
      const int& pin);

   // Not implemented in base class.
   // Note: ESP8266 and ESP32 have different calls for implementing this functionality.
   /*
   virtual void analogWrite(
      const int& pin,
      const int& value);
   */

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

   // This operation retrieves the MAC address of the board.
   virtual void getMacAddress(
      unsigned char macAddress[6]) const;

   // This operation retrieves the current IP address (if connected) of the board.
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

   // This operation return true if the board is connected to a Wifi network.
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
