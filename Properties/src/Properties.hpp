#pragma once

#include "Dictionary.hpp"
#include "Set.hpp"

class Properties : public Dictionary
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

    void getKeys(
      const String& namePrefix,
      Set<String>& keys) const;

   // Writes the contents of the properties file, line by line, to the Logger.
   void log() const;

private:

   bool parseLine(
      const String& line);

    String path;
};
