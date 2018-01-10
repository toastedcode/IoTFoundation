#include "Parameter.hpp"

Parameter::Parameter() :
   type(UNKNOWN)
{
   initialize();
}

Parameter::Parameter(const Parameter& parameter)
{
   name = parameter.name;
   memcpy(&value, &parameter.value, sizeof(ParameterValue));
   stringValue = parameter.stringValue;
   type = parameter.type;
}

Parameter::Parameter(const String& name) :
   type(UNKNOWN)
{
   initialize();
   setName(name);
}

Parameter::Parameter(const String& name, const bool& value)
{
   initialize();
   setName(name);
   setValue(value);
}

Parameter::Parameter(const String& name, const double& value)
{
   initialize();
   setName(name);
   setValue(value);
}

Parameter::Parameter(const String& name, const float& value)
{
   initialize();
   setName(name);
   setValue(value);
}

Parameter::Parameter(const String& name, const int& value)
{
   initialize();
   setName(name);
   setValue(value);
}

Parameter::Parameter(const String& name, const String& value)
{
   initialize();
   setName(name);
   setValue(value);
}

Parameter::~Parameter()
{
   // Nothing to do here.
}

void Parameter::initialize()
{
   type = UNKNOWN;
   name = "";
   memset(&value, 0, sizeof(ParameterValue));
}

void Parameter::setName(const String& name)
{
   this->name = name;
}

const String& Parameter::getName() const
{
   return (name);
}

bool Parameter::getBoolValue() const
{
   return (value.boolValue);
}

double Parameter::getDoubleValue() const
{
   return (value.doubleValue);
}

float Parameter::getFloatValue() const
{
   return (value.floatValue);
}

int Parameter::getIntValue() const
{
   return (value.intValue);
}

const String& Parameter::getStringValue() const
{
   return (stringValue);
}

Parameter::ParameterType Parameter::getType() const
{
   return (type);
}

void Parameter::setValue(const bool& value)
{
    this->value.boolValue = value;
    type = BOOL;
}

void Parameter::setValue(const double& value)
{
   this->value.doubleValue = value;
   type = DOUBLE;
}

void Parameter::setValue(const float& value)
{
   this->value.floatValue = value;
   type = FLOAT;
}

void Parameter::setValue(const int& value)
{
   this->value.intValue = value;
   type = INT;
}

void Parameter::setValue(const String& value)
{
   this->stringValue = value;
   type = STRING;
}

bool Parameter::operator==(
   const Parameter& rhs) const
{
   return ((name == rhs.name) &&
           (memcmp(&value, &rhs.value, sizeof(ParameterValue)) == 0) &&
           (stringValue == rhs.stringValue) &&
           (type == rhs.type));
}

Parameter& Parameter::operator=(
   const Parameter& rhs)
{
   if (this != &rhs)
   {
      name = rhs.name;
      memcpy(&value, &rhs.value, sizeof(ParameterValue));
      stringValue = rhs.stringValue;
      type = rhs.type;
   }

   return (*this);
}
