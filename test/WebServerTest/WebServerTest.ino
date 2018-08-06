#include "Esp8266Board.hpp"
#include "FS.h"
#include "Properties.hpp"
#include "PropertiesPage.hpp"
#include "WebServer.hpp"

const String PROPERTIES_FILE = "/robox.properties";

Properties properties;

WebServer webServer(80);

// *****************************************************************************
//                                  Arduino
// *****************************************************************************

void setup()
{
   Serial.begin(9600);
   SPIFFS.begin();
   
   Logger::setLogger(new SerialLogger());

   Logger::logDebug("\n\n********** Web Server Test **********\n\n");
   
   Board::setBoard(new Esp8266Board());

   // Load properties.
   properties.load(PROPERTIES_FILE);
   Logger::logDebug(F("Properties:"));
   properties.log();

   WifiBoard::getBoard()->connectWifi(properties.getString("wifi.ssid"), properties.getString("wifi.password"));

   webServer.setup();
   webServer.addPage(new PropertiesPage());
}

void loop()
{
   webServer.loop();
}
