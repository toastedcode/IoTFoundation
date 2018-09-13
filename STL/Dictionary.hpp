#pragma once

#include "CommonDefs.hpp"
#include "Map.hpp"

class Dictionary : public Map<String, String>
{

public:

   // Operations for getting properties.
   bool getBool(const String& name) const;
   char getChar(const String& name) const;
   double getDouble(const String& name) const;
   float getFloat(const String& name) const;
   int getInt(const String& name) const;
   String getString(const String& name) const;

   // Operations for setting properties.
   void set(const String& name, bool value);
   void set(const String& name, char value);
   void set(const String& name, double value);
   void set(const String& name, float value);
   void set(const String& name, int value);
   void set(const String& name, char* value);
   void set(const String& name, String value);

   void unset(const String& name);

   // Dumps the contents of the dictionary to a string.
   String toString() const;
};
