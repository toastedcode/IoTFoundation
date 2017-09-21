#include <FS.h>

#include "Board.hpp"
#include "Logger.hpp"
#include "Messaging.hpp"
#include "WebServer.hpp"

const int WebServer::MAX_WEBPAGES;

WebServer::WebServer(
   const int& port) :
     port(port),
     server(0)
{
   memset(webpages, 0, (sizeof(Webpage*) * MAX_WEBPAGES));
}

WebServer::~WebServer()
{
   // Nothing to do here.
}

void WebServer::setup()
{
   server = new ESP8266WebServer(port);
   server->addHandler(this);
   server->begin();
}

void WebServer::loop()
{
   server->handleClient();
}

bool WebServer::canHandle(
   HTTPMethod method,
   String uri)
{
   return (true);
}

bool WebServer::handle(
   ESP8266WebServer& server,
   HTTPMethod requestMethod,
   String requestUri)
{
   bool success = true;

   Logger::logDebug("WebServer::handle: %s", requestUri.c_str());

   success = servePage(server, requestMethod, requestUri);

   if (!success)
   {
      success = serveFile(server, requestMethod, requestUri);
   }

   if (!success)
   {
      handleNotFound(server, requestMethod, requestUri);
      success = true;
   }

   return (success);
}

void WebServer::handleNotFound(
   ESP8266WebServer& server,
   HTTPMethod requestMethod,
   String requestUri)
{
   server.send(404, "text/plain", "File not found.");
}

bool WebServer::addPage(
   Webpage* webpage)
{
   bool success = false;

   for (int i = 0; i < MAX_WEBPAGES; i++)
   {
      if (webpages[i] == 0)
      {
         webpages[i] = webpage;
         success = true;
      }
   }

   return (success);
}

Webpage* WebServer::getPage(
   const String& uri)
{
   Webpage* webpage = 0;

   for (int i = 0; i < MAX_WEBPAGES; i++)
   {
      if ((webpages[i] != 0) &&
          (webpages[i]->getUri() == uri))
      {
         webpage = webpages[i];
         break;
      }
   }

   return (webpage);
}

bool WebServer::removePage(
   const String& uri)
{
   bool success = false;

   for (int i = 0; i < MAX_WEBPAGES; i++)
   {
      if ((webpages[i] != 0) &&
          (webpages[i]->getUri() == uri))
      {
         webpages[i] = 0;
         success = true;
         break;
      }
   }

   return (success);
}

bool WebServer::servePage(
   ESP8266WebServer& server,
   HTTPMethod requestMethod,
   String requestUri)
{
   bool success = false;

   String content = "";

   Webpage* webpage = getPage(requestUri);

   if ((webpage != 0) && (webpage->canHandle(requestMethod, requestUri)))
   {
      Logger::logDebug("WebServer::servePage: %s", requestUri.c_str());

      int numArguments = 0;
      getArguments(server, arguments, numArguments);

      String contentFile = "";
      if (webpage->handle(requestMethod, requestUri, arguments, numArguments, contentFile))
      {
         success = serveFile(server, requestMethod, contentFile);
      }
   }

   return (success);
}

bool WebServer::serveFile(
   ESP8266WebServer& server,
   HTTPMethod requestMethod,
   String requestUri)
{
   bool success = false;

   // Determine the data type based on the file extension.
   String dataType = getDataType(requestUri);

   // Attempt to open the file from the SPIFFS file system.
   File file = SPIFFS.open(requestUri.c_str(), "r");

   if (file)
   {
      Logger::logDebug("WebServer::serveFile: %s", requestUri.c_str());

      if (server.hasArg("download"))
      {
         dataType = "application/octet-stream";
      }

      // Send the file contents.
      if (server.streamFile(file, dataType) != file.size())
      {
         Logger::logWarning("WebServer::serveFile: Sent less data than expected.");
         success = true;
      }
      else
      {
         success = true;
      }

      file.close();
   }

   return (success);
}

String WebServer::getDataType(
   const String& path)
{
   String dataType = "text/plain";

   if ((path.endsWith(".htm")) ||
       (path.endsWith(".html")))
   {
      dataType = "text/html";
   }
   else if (path.endsWith(".css"))
   {
      dataType = "text/css";
   }
   else if (path.endsWith(".js"))
   {
      dataType = "application/javascript";
   }
   else if (path.endsWith(".png"))
   {
      dataType = "image/png";
   }
   else if (path.endsWith(".gif"))
   {
      dataType = "image/gif";
   }
   else if (path.endsWith(".jpg"))
   {
      dataType = "image/jpeg";
   }
   else if (path.endsWith(".ico"))
   {
      dataType = "image/x-icon";
   }
   else if (path.endsWith(".xml"))
   {
      dataType = "text/xml";
   }
   else if (path.endsWith(".pdf"))
   {
      dataType = "application/pdf";
   }
   else if (path.endsWith(".zip"))
   {
      dataType = "application/zip";
   }

   return (dataType);
}

void WebServer::getArguments(
   ESP8266WebServer& server,
   Argument arguments[],
   int& numArguments)
{
   for (int i = 0; i < MAX_ARGUMENTS; i++)
   {
      if (i < server.args())
      {
         arguments[i].setName(server.argName(i));
         arguments[i].setValue(server.arg(i));
      }
      else
      {
         arguments[i].setName("");
         arguments[i].setValue("");
      }
   }

   numArguments = server.args();
}

