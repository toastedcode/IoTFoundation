#include "EspSpiffs.hpp"
#include "Logger.hpp"
#include "Properties.hpp"
#include "StringUtils.hpp"

Properties::Properties() : Dictionary()
{
   path = "";
}

Properties::Properties(
   const String& path) : Dictionary()
{
   load(path);
}

Properties::~Properties()
{
   // Nothing to do here.
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
         if (size() > 0)
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
   const String& namePrefix,
   Set<String>& keys) const
{
   static const String DELIMITER = "%";

   keys.clear();

   for (Dictionary::Iterator it = begin(); it != end(); it++)
   {
      if (it->first.startsWith(namePrefix + DELIMITER))
      {
         keys.insert((*it).first);
      }
   }
}

void Properties::log() const
{
   for (Dictionary::Iterator it = begin(); it != end(); it++)
   {
      Logger::logDebug("%s = %s", it->first.c_str(), it->second.c_str());
   }
}

bool Properties::parseLine(
   const String& line)
{
   bool success = false;

   int pos = StringUtils::findFirstNotOf(line, " \t");

   if (line.charAt(pos) == '#')
   {
      // Ignore comments.
      success = true;
   }
   else
   {
      pos = StringUtils::findFirstOf(line, "=");

      if (pos < line.length())
      {
         String lhs = line.substring(0, pos);
         String rhs = line.substring(pos + 1);

         // Remove leading/trailing whitespace.
         lhs.trim();
         rhs.trim();

         if ((lhs.length() > 0) &&
             (rhs.length() > 0))
         {
            put(lhs, rhs);
            success = true;
         }
      }
   }

   return (success);
}
