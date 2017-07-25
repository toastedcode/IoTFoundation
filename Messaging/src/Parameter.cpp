#include <cstring>

#include "Parameter.hpp"

Parameter::Parameter() :
   type(UNKNOWN)
{
   initialize();
}

Parameter::Parameter(const char* name) :
   type(UNKNOWN)
{
   initialize();
   setName(name);
}

Parameter::Parameter(const char* name, const bool& value)
{
   initialize();
   setName(name);
   setValue(value);
}

Parameter::Parameter(const char* name, const double& value)
{
   initialize();
   setName(name);
   setValue(value);
}

Parameter::Parameter(const char* name, const float& value)
{
   initialize();
   setName(name);
   setValue(value);
}

Parameter::Parameter(const char* name, const int& value)
{
   initialize();
   setName(name);
   setValue(value);
}

Parameter::Parameter(const char* name, const char* value)
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
   memset(this->name, 0, sizeof(ParameterName));
   memset(&this->value, 0, sizeof(ParameterValue));
}

void Parameter::setName(const char* name)
{
   strncpy(this->name, name, sizeof(ParameterName));
}

const char* Parameter::getName() const
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

const char* Parameter::getStringValue() const
{
   return (value.stringValue);
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

void Parameter::setValue(const char* value)
{
   strncpy(this->value.stringValue, value, sizeof(StringValue));
   type = STRING;
}

bool Parameter::operator==(
   const Parameter& rhs) const
{
   return ((strncmp(name, rhs.name, sizeof(ParameterName)) == 0) &&
           (memcmp(&value, &rhs.value, sizeof(ParameterValue)) == 0) &&
           (type == rhs.type));
}

Parameter& Parameter::operator=(
   const Parameter& rhs)
{
   if (this != &rhs)
   {
      strncpy(name, rhs.name, sizeof(ParameterName));
      memcpy(&value, &rhs.value, sizeof(ParameterValue));
      type = rhs.type;
   }

   return (*this);
}
