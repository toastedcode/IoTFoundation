#pragma once

#include "ListMap.hpp"

class Properties
{

public:

   Properties();

   Properties(
      const String& path);

   virtual ~Properties();

   bool load(
      const String& path);

   bool save();

   bool saveAs(
      const String& path);

   // Operations for getting properties.
   bool getBool(const String& name) const;
   char getChar(const String& name) const;
   double getDouble(const String& name) const;
   float getFloat(const String& name) const;
   int getInt(const String& name) const;
   String getString(const String& name) const;

   void getKeys(
      String keys[],
      int& count) const;

   void getKeys(
      const String& namePrefix,
      String keys[],
      int& count) const;

   // Operations for setting properties.
   void set(const String& name, bool value);
   void set(const String& name, char value);
   void set(const String& name, double value);
   void set(const String& name, float value);
   void set(const String& name, int value);
   void set(const String& name, char* value);
   void set(const String& name, String value);

   // Operations for clearing properties.
   void remove(const String& name);

   // Returns true if the property file has the specified property set.
   bool isSet(
      // The name of the parameter to evaluate.
      const String& name) const;

   // Dumps the contents of the properties file to a string.
   String toString() const;

   // Writes the contents of the properties file, line by line, to the Logger.
   void log() const;

private:

   bool parseLine(
      const String& line);

   typedef Map<String, String> PropertyMap;

   PropertyMap* propertyMap;

   String path;

};
