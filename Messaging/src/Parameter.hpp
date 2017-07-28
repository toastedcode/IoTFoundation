#pragma once

class Parameter
{

public:

   static const int PARAMETER_NAME_SIZE = 15;

   static const int PARAMETER_VALUE_SIZE = 64;

   typedef char ParameterName[PARAMETER_NAME_SIZE];

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
   Parameter(const char* name);
   Parameter(const char* name, const bool& value);
   Parameter(const char* name, const double& value);
   Parameter(const char* name, const float& value);
   Parameter(const char* name, const int& value);
   Parameter(const char* name, const char* value);

   virtual ~Parameter();

   void initialize();

   const char* getName() const;

   void setName(const char* name);

   bool getBoolValue() const;
   double getDoubleValue() const;
   float getFloatValue() const;
   int getIntValue() const;
   const char* getStringValue() const;

   ParameterType getType() const;

   void setValue(const bool& value);
   void setValue(const double& value);
   void setValue(const float& value);
   void setValue(const int& value);
   void setValue(const char* value);

   bool operator==(
      const Parameter& rhs) const;

   Parameter& operator=(
      const Parameter& rhs);

private:

   typedef char StringValue[PARAMETER_VALUE_SIZE];

   union ParameterValue
   {
      bool boolValue;

      double doubleValue;

      float floatValue;

      int intValue;

      StringValue stringValue;
   };

   ParameterName name;

   ParameterValue value;

   ParameterType type;
};
