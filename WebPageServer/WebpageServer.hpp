#pragma once

#include "Dictionary.hpp"
#include "EspWebServer.hpp"
#include "EspWifi.hpp"
#include "Webpage.hpp"

class WebpageServer : public RequestHandler
{

public:

   WebpageServer(
      const int& port);

   virtual ~WebpageServer();

   virtual void setup();

   virtual void loop();

   // **************************************************************************
   // RequestHandler operations

   virtual bool canHandle(
      HTTPMethod method,
      String uri);

   virtual bool handle(
      EspWebServer& server,
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
      EspWebServer& server,
      HTTPMethod requestMethod,
      String requestUri);

   bool serveFile(
      EspWebServer& server,
      HTTPMethod requestMethod,
      String requestUri);

   virtual void handleNotFound(
      EspWebServer& server,
      HTTPMethod requestMethod,
      String requestUri);

   static String getDataType(
      const String& path);

   static void getArguments(
      EspWebServer& server,
      Dictionary& arguments);

private:

   int port;

   EspWebServer* server;

   Map<String, Webpage*> webpages;
};

