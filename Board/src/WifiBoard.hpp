// *****************************************************************************
// *****************************************************************************
// WifiBoard.hpp
//
// Author: Jason Tost
// Date:   10.17.2016
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "Board.hpp"

class WifiBoard : public Board
{

public:

   // Destructor.
   virtual ~WifiBoard() = 0;

   static WifiBoard* getBoard();

   // This operation retrieves the MAC address of the board.
   virtual void getMacAddress(
      unsigned char macAddress[6]) const;

   // This operation retrieves the current IP address (if connected) of the board.
   virtual String getIpAddress() const = 0;

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
   virtual bool disconnectWifi() = 0;

   // This operation return true if the ESP8266 is connected to a Wifi network.
   virtual bool isConnected() const = 0;

   // This operation attempts to create a Wifi access point.
   // True is returned if the operation was successful; false otherwise.
   // Note: This operation blocks while attempting to make the AP.
   virtual bool startAccessPoint(
      // The SSID to use in connecting.
      const String& ssid,
      // The password to use in connecting.
      const String& password) = 0;

   // This operation stops any currently started Wifi access point.
   // True is returned if the operation was successful; false otherwise.
   virtual bool stopAccessPoint() = 0;
};

inline WifiBoard::~WifiBoard() {}

inline WifiBoard* WifiBoard::getBoard()
{
   return ((WifiBoard*)Board::getBoard());
}
