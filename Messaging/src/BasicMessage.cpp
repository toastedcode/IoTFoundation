#include "BasicMessage.hpp"

int BasicMessage::getParameterCount()
{
   return (parameters.length());
}

Parameter BasicMessage::getParameter(
   const int& index)
{
   Parameter parameter;

   if (index < parameters.length())
   {
      parameter = parameters.item(index)->value;
   }

   return (parameter);
}

Parameter BasicMessage::getParameter(
   const ParameterName& name)
{
   Parameter parameter;

   if (isSet(name))
   {
      parameter = *(parameters.get(name));
   }

   return (parameter);
}

void BasicMessage::setParameter(
   const Parameter& parameter)
{
   parameters.put(parameter.name, parameter);
}

bool BasicMessage::getBool(ParameterName name) const
{
   bool b = false;

   const Parameter* parameter = parameters.get(name);
   if (parameter != 0)
   {
      String lowerCase = parameter->value;
      lowerCase.toLowerCase();

      b = (lowerCase == "true");
   }

   return (b);
}
