#pragma once

#include "CommonDefs.hpp"

class Parameter
{

public:

   typedef String ParameterName;

   enum ParameterType
   {
      UNKNOWN,
      BOOL,
      DOUBLE,
      FLOAT,
      INT,
      STRING,
   };

   Parameter();
   Parameter(const Parameter& parameter);
   Parameter(const String& name);
   Parameter(const String& name, const bool& value);
   Parameter(const String& name, const double& value);
   Parameter(const String& name, const float& value);
   Parameter(const String& name, const int& value);
   Parameter(const String& name, const String& value);

   virtual ~Parameter();

   void initialize();

   const String& getName() const;

   void setName(const String& name);

   bool getBoolValue() const;
   double getDoubleValue() const;
   float getFloatValue() const;
   int getIntValue() const;
   const String& getStringValue() const;

   ParameterType getType() const;

   void setValue(const bool& value);
   void setValue(const double& value);
   void setValue(const float& value);
   void setValue(const int& value);
   void setValue(const String& value);

   bool operator==(
      const Parameter& rhs) const;

   Parameter& operator=(
      const Parameter& rhs);

private:

   union ParameterValue
   {
      bool boolValue;

      double doubleValue;

      float floatValue;

      int intValue;
   };

   String stringValue;

   ParameterName name;

   ParameterValue value;

   ParameterType type;
};
