#include "Esp32Board.hpp"
#include "EspSpiffs.hpp"
#include "EspWebServer.hpp"
#include "Properties.hpp"
#include "PropertiesPage.hpp"
#include "WebpageServer.hpp"

const String PROPERTIES_FILE = "/robox.properties";

Properties properties;

WebpageServer webpageServer(80);

// *****************************************************************************
//                                  Arduino
// *****************************************************************************

void setup()
{
   Serial.begin(9600);
   SPIFFS.begin();
   
   Logger::setLogger(new SerialLogger());

   Logger::logDebug("\n\n********** Web Server Test **********\n\n");
   
   Board::setBoard(new Esp32Board());

   // Load properties.
   properties.load(PROPERTIES_FILE);
   Logger::logDebug(F("Properties:"));
   properties.log();

   WifiBoard::getBoard()->connectWifi(properties.getString("wifi.ssid"), properties.getString("wifi.password"));

   webpageServer.setup();
   webpageServer.addPage(new PropertiesPage());
}

void loop()
{
   webpageServer.loop();
}
