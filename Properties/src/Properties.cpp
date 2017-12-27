#include <FS.h>

#include "Logger.hpp"
#include "Properties.hpp"
#include "StringUtils.hpp"

Properties::Properties()
{
   propertyMap = new ListMap<String, String>();
   path = "";
}

Properties::Properties(
   const String& path) :
      path(path)
{
   load(path);
}

Properties::~Properties()
{
}

bool Properties::load(
   const String& path)
{
   bool success = false;

   File file = SPIFFS.open(path, "r");
   if (!file)
   {
      Logger::logWarning(F("Properties::load: Failed to load property file: %s"), path.c_str());
   }
   else
   {
      this->path = path;

      String line = file.readStringUntil('\n');
      while (line.length() > 0)
      {
         parseLine(line);

         line = file.readStringUntil('\n');
      }

      file.close();

      Logger::logDebug(F("Properties::load: Loaded properties file: %s"), path.c_str());
      success = true;
   }

   return (success);
}

bool Properties::save()
{
   bool success = false;

   if (path.length() == 0)
   {
      Logger::logWarning(F("Properties::save: No filename specified."));
   }
   else
   {
      success = saveAs(path);
   }

   return (success);
}

bool Properties::saveAs(
   const String& path)
{
   bool success = false;

   if (path.length() > 0)
   {
      File file = SPIFFS.open(path, "w");
      if (!file)
      {
         Logger::logWarning(F("Properties::saveAs: Failed to write to property file: %s"), path.c_str());
      }
      else
      {
         if (propertyMap->length() > 0)
         {
            file.print(toString());
         }

         file.close();

         Logger::logDebug(F("Properties::saveAs: Saved properties file: %s"), path.c_str());
         success = true;
      }
   }

   return (success);
}

void Properties::getKeys(
   Set<String>& keys) const
{
   keys.clear();

   for (PropertyMap::Iterator it = propertyMap->begin(); it != propertyMap->end(); it++)
   {
      keys.insert((*it).key);
   }
}

void Properties::getKeys(
   const String& namePrefix,
   Set<String>& keys) const
{
   static const String DELIMITER = "%";

   keys.clear();

   for (PropertyMap::Iterator it = propertyMap->begin(); it != propertyMap->end(); it++)
   {
      if ((*it).key.startsWith(namePrefix + DELIMITER))
      {
         keys.insert((*it).key);
      }
   }
}

bool Properties::getBool(const String& name) const
{
   bool value = false;

   Map<String, String>::Iterator foundIt = propertyMap->find(name);
   if (foundIt != propertyMap->end())
   {
      String lowerCase = foundIt->second;
      lowerCase.toLowerCase();

      value = (lowerCase == "true");
   }

   return (value);
}

char Properties::getChar(const String& name) const
{
   char value = 0;

   Map<String, String>::Iterator foundIt = propertyMap->find(name);
   if (foundIt != propertyMap->end())
   {
      value = foundIt->second.charAt(0);
   }

   return (value);
}

double Properties::getDouble(const String& name) const
{
   double value = 0;

   if (propertyMap->isSet(name))
   {
      // TODO
      //value = parameters.get(name)->toDouble();
   }

   return (value);
}

float Properties::getFloat(const String& name) const
{
   float value = 0;

   Map<String, String>::Iterator foundIt = propertyMap->find(name);
   if (foundIt != propertyMap->end())
   {
      value = foundIt->second.toFloat();
   }

   return (value);
}

int Properties::getInt(const String& name) const
{
   int value = 0;

   Map<String, String>::Iterator foundIt = propertyMap->find(name);
   if (foundIt != propertyMap->end())
   {
      value = foundIt->second.toInt();
   }

   return (value);
}

String Properties::getString(const String& name) const
{
   String value = "";

   Map<String, String>::Iterator foundIt = propertyMap->find(name);
   if (foundIt != propertyMap->end())
   {
      value = foundIt->second;
   }

   return (value);
}

void Properties::set(const String& name, bool value)
{
   propertyMap->put(name, (value ? "true" : "false"));
}

void Properties::set(const String& name, char value)
{
   propertyMap->put(name, String(value));
}

void Properties::set(const String& name, double value)
{
   propertyMap->put(name, String(value));
}

void Properties::set(const String& name, float value)
{
   propertyMap->put(name, String(value));
}

void Properties::set(const String& name, int value)
{
   propertyMap->put(name, String(value));
}

void Properties::set(const String& name, char* value)
{
   propertyMap->put(name, String(value));
}

void Properties::set(const String& name, String value)
{
   propertyMap->put(name, String(value));
}

void Properties::remove(const String& name)
{
   if (propertyMap->isSet(name))
   {
      propertyMap->erase(name);
   }
}

bool Properties::isSet(
   const String& name) const
{
   return (propertyMap->isSet(name));
}

String Properties::toString() const
{
   String s;

   for (PropertyMap::Iterator it = propertyMap->begin(); it != propertyMap.end(); it++)
   {
      s += it->first + " = " + it->second + "\n";
   }

   return (s);
}

void Properties::log() const
{
   for (PropertyMap::Iterator it = propertyMap->begin(); it != propertyMap.end(); it++)
   {
      Logger::logDebug("%s = %s", it->first.c_str(), it->second.c_str());
   }
}

bool Properties::parseLine(
   const String& line)
{
   bool success = false;

   int pos = StringUtils::findFirstOf(line, "=");

   if (pos < line.length())
   {
      String lhs = line.substring(0, pos);
      String rhs = line.substring(pos + 1);

      // TODO: Implment a trim function.
      lhs = StringUtils::removeAll(lhs, " \n\r");
      rhs = StringUtils::removeAll(rhs, " \n\r");

      if ((lhs.length() > 0) &&
          (rhs.length() > 0))
      {
         propertyMap->put(lhs, rhs);
         success = true;
      }
   }

   return (success);
}
