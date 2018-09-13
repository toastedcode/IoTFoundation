#include "Dictionary.hpp"

bool Dictionary::getBool(const String& name) const
{
   bool value = false;

   Map<String, String>::Iterator foundIt = find(name);
   if (foundIt != end())
   {
      String lowerCase = foundIt->second;
      lowerCase.toLowerCase();

      value = (lowerCase == "true");
   }

   return (value);
}

char Dictionary::getChar(const String& name) const
{
   char value = 0;

   Map<String, String>::Iterator foundIt = find(name);
   if (foundIt != end())
   {
      value = foundIt->second.charAt(0);
   }

   return (value);
}

double Dictionary::getDouble(const String& name) const
{
   double value = 0;

   if (isSet(name))
   {
      // TODO
      //value = get(name)->toDouble();
   }

   return (value);
}

float Dictionary::getFloat(const String& name) const
{
   float value = 0;

   Map<String, String>::Iterator foundIt = find(name);
   if (foundIt != end())
   {
      value = foundIt->second.toFloat();
   }

   return (value);
}

int Dictionary::getInt(const String& name) const
{
   int value = 0;

   Map<String, String>::Iterator foundIt = find(name);
   if (foundIt != end())
   {
      value = foundIt->second.toInt();
   }

   return (value);
}

String Dictionary::getString(const String& name) const
{
   String value = "";

   Map<String, String>::Iterator foundIt = find(name);
   if (foundIt != end())
   {
      value = foundIt->second;
   }

   return (value);
}

void Dictionary::set(const String& name, bool value)
{
   put(name, (value ? "true" : "false"));
}

void Dictionary::set(const String& name, char value)
{
   put(name, String(value));
}

void Dictionary::set(const String& name, double value)
{
   put(name, String(value));
}

void Dictionary::set(const String& name, float value)
{
   put(name, String(value));
}

void Dictionary::set(const String& name, int value)
{
   put(name, String(value));
}

void Dictionary::set(const String& name, char* value)
{
   put(name, String(value));
}

void Dictionary::set(const String& name, String value)
{
   put(name, String(value));
}

void Dictionary::unset(const String& name)
{
   erase(name);
}

String Dictionary::toString() const
{
   String s;

   for (Map<String, String>::Iterator it = begin(); it != end(); it++)
   {
      s += it->first + " = " + it->second + "\n";
   }

   return (s);
}
