#include "Board.hpp"
#include "EspSpiffs.hpp"
#include "Logger.hpp"
#include "Messaging.hpp"
#include "WebpageServer.hpp"

WebpageServer::WebpageServer(
   const int& port) :
     port(port),
     server(0)
{
   // Nothing to do here.
}

WebpageServer::~WebpageServer()
{
   // Nothing to do here.
}

void WebpageServer::setup()
{
   Logger::logDebug(F("WebpageServer::setup: Starting web server on port %d."), port);

   server = new EspWebServer(port);
   server->addHandler(this);
   server->begin();
}

void WebpageServer::loop()
{
   server->handleClient();
}

bool WebpageServer::canHandle(
   HTTPMethod method,
   String uri)
{
   return (true);
}

bool WebpageServer::handle(
   EspWebServer& server,
   HTTPMethod requestMethod,
   String requestUri)
{
   bool success = true;

   Logger::logDebug(F("WebpageServer::handle: %s"), requestUri.c_str());

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

void WebpageServer::handleNotFound(
   EspWebServer& server,
   HTTPMethod requestMethod,
   String requestUri)
{
   server.send(404, "text/plain", "File not found.");
}

void WebpageServer::addPage(
   Webpage* webpage)
{
   Logger::logDebug(F("WebpageServer::addPage: Hosting webpage: %s"), webpage->getUri().c_str());

   webpages[webpage->getUri()] = webpage;
}

Webpage* WebpageServer::getPage(
   const String& uri)
{
   Webpage* webpage = 0;

   Map<String, Webpage*>::Iterator findIt = webpages.find(uri);
   if (findIt !=  webpages.end())
   {
      webpage = findIt->second;
   }

   return (webpage);
}

void WebpageServer::removePage(
   const String& uri)
{
   webpages.erase(uri);
}

bool WebpageServer::servePage(
   EspWebServer& server,
   HTTPMethod requestMethod,
   String requestUri)
{
   bool success = false;

   String content = "";

   Webpage* webpage = getPage(requestUri);

   if ((webpage != 0) && (webpage->canHandle(requestMethod, requestUri)))
   {
      Logger::logDebug(F("WebpageServer::servePage: %s"), requestUri.c_str());

      Dictionary arguments;
      getArguments(server, arguments);

      String contentFile = "";
      if (webpage->handle(requestMethod, requestUri, arguments, contentFile))
      {
         success = serveFile(server, requestMethod, contentFile);
      }
   }

   return (success);
}

bool WebpageServer::serveFile(
   EspWebServer& server,
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
      Logger::logDebug(F("WebpageServer::serveFile: %s (%d bytes)"), requestUri.c_str(), file.size());

      if (server.hasArg("download"))
      {
         dataType = "application/octet-stream";
      }

      // Send the file contents.
      int bytesSent = server.streamFile(file, dataType);
      if (bytesSent != file.size())
      {
         Logger::logWarning(F("WebpageServer::serveFile: Sent less data than expected. (%d/%d)"), bytesSent, file.size());
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

String WebpageServer::getDataType(
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

void WebpageServer::getArguments(
   EspWebServer& server,
   Dictionary& arguments)
{
   for (int i = 0; i < server.args(); i++)
   {
      arguments[server.argName(i)] = server.arg(i);
   }
}
