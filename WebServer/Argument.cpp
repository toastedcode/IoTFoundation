#include "Argument.hpp"
#include "StringUtils.hpp"


Argument::Argument() :
   name(""),
   value("")
{
   // Nothing to do here.
}

Argument::Argument(const String& name) :
   Argument()
{
   setName(name);
}

Argument::Argument(const String& name, const bool& value)
{
   setName(name);
   setValue(value);
}

Argument::Argument(const String& name, const double& value)
{
   setName(name);
   setValue(value);
}

Argument::Argument(const String& name, const float& value)
{
   setName(name);
   setValue(value);
}

Argument::Argument(const String& name, const int& value)
{
   setName(name);
   setValue(value);
}

Argument::Argument(const String& name, const String& value)
{
   setName(name);
   setValue(value);
}

Argument::~Argument()
{
   // Nothing to do here.
}

const String& Argument::getName() const
{
   return (name);
}

void Argument::setName(const String& name)
{
   this->name = name;
}

bool Argument::getBoolValue() const
{
   return (StringUtils::toBool(value));
}

double Argument::getDoubleValue() const
{
   // TODO: Handle double
   return ((double)value.toFloat());
}

float Argument::getFloatValue() const
{
   return (value.toFloat());
}

int Argument::getIntValue() const
{
   // TODO: Fix trucation of longs.
   long longValue = value.toInt();
   return ((int)longValue);
}

String Argument::getStringValue() const
{
   return (value);
}

void Argument::setValue(const bool& value)
{
   this->value = String(value);
}

void Argument::setValue(const double& value)
{
   this->value = String(value);
}

void Argument::setValue(const float& value)
{
   this->value = String(value);
}

void Argument::setValue(const int& value)
{
   this->value = String(value);
}

void Argument::setValue(const String& value)
{
   this->value = String(value);
}

bool Argument::operator==(
   const Argument& rhs) const
{
   return ((name == rhs.name) &&
           (value == rhs.value));
}

Argument& Argument::operator=(
   const Argument& rhs)
{
   if (this != &rhs)
   {
      setName(rhs.getName());
      setValue(rhs.getStringValue());
   }

   return (*this);
}

bool Argument::hasArgument(Argument arguments[], const int& numArguments, const String& name)
{
   return (getArgument(arguments, numArguments, name) != 0);
}

const Argument* Argument::getArgument(Argument arguments[], const int& numArguments, const String& name)
{
   const Argument* argument = 0;

   for (int i = 0; i < numArguments; i++)
   {
      if (arguments[i].getName() == name)
      {
         argument = &arguments[i];
      }
   }

   return (argument);
}
