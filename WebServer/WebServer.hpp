#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "Dictionary.hpp"
#include "Webpage.hpp"

class WebServer : public RequestHandler
{

public:

   WebServer(
      const int& port);

   virtual ~WebServer();

   virtual void setup();

   virtual void loop();

   // **************************************************************************
   // RequestHandler operations

   virtual bool canHandle(
      HTTPMethod method,
      String uri);

   virtual bool handle(
      ESP8266WebServer& server,
      HTTPMethod requestMethod,
      String requestUri);

   // **************************************************************************

   void addPage(
      Webpage* webpage);

   Webpage* getPage(
      const String& uri);

   void removePage(
      const String& uri);

protected:

   bool servePage(
      ESP8266WebServer& server,
      HTTPMethod requestMethod,
      String requestUri);

   bool serveFile(
      ESP8266WebServer& server,
      HTTPMethod requestMethod,
      String requestUri);

   virtual void handleNotFound(
      ESP8266WebServer& server,
      HTTPMethod requestMethod,
      String requestUri);

   static String getDataType(
      const String& path);

   static void getArguments(
      ESP8266WebServer& server,
      Dictionary& arguments);

private:

   int port;

   ESP8266WebServer* server;

   Map<String, Webpage*> webpages;
};
