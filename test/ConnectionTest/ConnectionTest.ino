//#include "Connection/Connection.hpp"
#include <ToastBot.h>

#include "Esp8266Board.hpp"

MqttClientAdapter* onlineAdapter = NULL;

void setup()
{
   Serial.begin(9600);

   ESP.wdtDisable();  // To prevent WDT reset
      
   Logger::setLogger(new SerialLogger());
   
   Board::setBoard(new Esp8266Board());

   Connection::setApConfig("RoboxAP", "password");
   
   Connection::setWifiConfig("REDACTED", "REDACTED");
   
   Connection::setServerConfig(
      "broker.hivemq.com",  //server
      1883,                 // port
      "",                   // userId
      "",                   // password
      "robox123",           // client ID
      "roboxes");           // topic

   onlineAdapter = new MqttClientAdapter("online", new JsonProtocol());

   Connection::setOnlineAdapter(onlineAdapter);

   ServerConfig serverConfig = Connection::getServerConfig();
   onlineAdapter->setServer(serverConfig.host, serverConfig.port);
   onlineAdapter->setClientId(serverConfig.clientId);
   onlineAdapter->setUser(serverConfig.userId, serverConfig.password);
   onlineAdapter->setTopic(serverConfig.topic);  

   Serial.println("Select a connection mode: \n1) NONE, \n2 AP \n3) WIFI \n4) ONLINE\n)");

   ESP.wdtEnable(1000);
}

void loop()
{
   onlineAdapter->loop();

   if (Serial.available())
   {
      int input = Serial.read();

      switch ((char)input)
      {
         case '1':
         {
            Connection::setMode(OFFLINE);
            break;
         }

         case '2':
         {
            Connection::setMode(ACCESS_POINT);
            break;
         }

         case '3':
         {
            Connection::setMode(WIFI);
            break;
         }

         case '4':
         {
            Connection::setMode(ONLINE);
            break;
         }

         default:
         {
            Serial.println("Invalid input");
            
         }
     }
   }
}
