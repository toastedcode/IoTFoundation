#pragma once

#include "CommonDefs.hpp"

class Argument
{

public:

   Argument();
   Argument(const String& name);
   Argument(const String& name, const bool& value);
   Argument(const String& name, const double& value);
   Argument(const String& name, const float& value);
   Argument(const String& name, const int& value);
   Argument(const String& name, const String& value);

   virtual ~Argument();

   const String& getName() const;

   void setName(const String& name);

   bool getBoolValue() const;
   double getDoubleValue() const;
   float getFloatValue() const;
   int getIntValue() const;
   String getStringValue() const;

   void setValue(const bool& value);
   void setValue(const double& value);
   void setValue(const float& value);
   void setValue(const int& value);
   void setValue(const String& value);

   bool operator==(
      const Argument& rhs) const;

   Argument& operator=(
      const Argument& rhs);

   static bool hasArgument(Argument arguments[], const int& numArguments, const String& name);

   static const Argument* getArgument(Argument arguments[], const int& numArguments, const String& name);

private:

   String name;

   String value;
};
