#include <FS.h>

#include "Logger.hpp"
#include "Properties.hpp"
#include "StringUtils.hpp"

Properties::Properties()
{
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
      Logger::logWarning("Properties::load: Failed to open property file: %s", path.c_str());
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

      success = true;
   }

   return (success);
}

bool Properties::save()
{
   bool success = false;

   if (path.length() == 0)
   {
      Logger::logWarning("Properties::save: No filename specified.");
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
         Logger::logWarning("Properties::saveAs: Failed to write to property file: %s", path.c_str());
      }
      else
      {
         if (propertyMap.length() > 0)
         {
            file.print(toString());
         }

         file.close();

         Logger::logDebug("Properties::saveAs: Saved properties file: %s", path.c_str());
         success = true;
      }
   }

   return (success);
}

void Properties::getKeys(
   String keys[],
   int& count) const
{
   for (int i = 0; i < propertyMap.length(); i++)
   {
      const PropertyMap::Entry* entry = propertyMap.item(i);

      keys[i] = entry->key;
      count++;
   }
}

void Properties::getKeys(
   const String& namePrefix,
   String keys[],
   int& count) const
{
   static const String DELIMITER = "%";

   for (int i = 0; i < propertyMap.length(); i++)
   {
      const PropertyMap::Entry* entry = propertyMap.item(i);

      if (entry->key.startsWith(namePrefix + DELIMITER))
      {
         keys[count] = entry->key;
         count++;
      }
   }
}

bool Properties::getBool(const String& name) const
{
   bool value = false;

   if (propertyMap.isSet(name))
   {
      String lowerCase = *(propertyMap.get(name));
      lowerCase.toLowerCase();

      value = (lowerCase == "true");
   }

   return (value);
}

char Properties::getChar(const String& name) const
{
   char value = 0;

   if ((propertyMap.isSet(name)) &&
       (propertyMap.get(name)->length() > 0))
   {
      value = propertyMap.get(name)->charAt(0);
   }

   return (value);
}

double Properties::getDouble(const String& name) const
{
   double value = 0;

   if (propertyMap.isSet(name))
   {
      // TODO
      //value = parameters.get(name)->toDouble();
   }

   return (value);
}

float Properties::getFloat(const String& name) const
{
   float value = 0;

   if (propertyMap.isSet(name))
   {
      value = propertyMap.get(name)->toFloat();
   }

   return (value);
}

int Properties::getInt(const String& name) const
{
   int value = 0;

   if (propertyMap.isSet(name))
   {
      value = propertyMap.get(name)->toInt();
   }

   return (value);
}

String Properties::getString(const String& name) const
{
   String value = "";

   if (propertyMap.isSet(name))
   {
      value = *(propertyMap.get(name));
   }

   return (value);
}

void Properties::set(const String& name, bool value)
{
   propertyMap.put(name, (value ? "true" : "false"));
}

void Properties::set(const String& name, char value)
{
   propertyMap.put(name, String(value));
}

void Properties::set(const String& name, double value)
{
   propertyMap.put(name, String(value));
}

void Properties::set(const String& name, float value)
{
   propertyMap.put(name, String(value));
}

void Properties::set(const String& name, int value)
{
   propertyMap.put(name, String(value));
}

void Properties::set(const String& name, char* value)
{
   propertyMap.put(name, String(value));
}

void Properties::set(const String& name, String value)
{
   propertyMap.put(name, String(value));
}

void Properties::remove(const String& name)
{
   if (propertyMap.isSet(name))
   {
      propertyMap.erase(name);
   }
}

bool Properties::isSet(
   const String& name) const
{
   return (propertyMap.isSet(name));
}

String Properties::toString() const
{
   String s;

   for (int i = 0; i < propertyMap.length(); i++)
   {
      const PropertyMap::Entry* entry = propertyMap.item(i);

      s += entry->key + " = " + entry->value + "\n";
   }

   return (s);
}

void Properties::log() const
{
   for (int i = 0; i < propertyMap.length(); i++)
   {
      const PropertyMap::Entry* entry = propertyMap.item(i);
      Logger::logDebug("%s = %s", entry->key.c_str(), entry->value.c_str());
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
         propertyMap.put(lhs, rhs);
         success = true;
      }
   }

   return (success);
}
