// *****************************************************************************
// *****************************************************************************
// MessagingDefs.hpp
//
// Author: Jason Tost
// Date:   5.26.2016
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "CommonDefs.hpp"

typedef String MessageId;

typedef String HandlerId;

typedef String Topic;

typedef String ParameterName;

enum ParameterType
{
   UNKNOWN,
   ARRAY,
   BOOL,
   CHAR,
   DOUBLE,
   FLOAT,
   INT,
   STRING,
   OBJECT,
};

struct Parameter
{
   String name;

   String value;

   ParameterType type;

   Parameter() : name(""),
                 value(""),
                 type(UNKNOWN)
   {
   }

   Parameter(
      const ParameterName& name,
      const String& value,
      const ParameterType& type) : name(name),
                                   value(value),
                                   type(type)
   {
   }

   bool operator==(
      const Parameter& rhs) const
   {
      return ((name == rhs.name) && (value == rhs.value) && (type == rhs.type));
   }

   Parameter& operator=(
      const Parameter& rhs)
   {
      if (this != &rhs)
      {
         name = rhs.name;
         value = rhs.value;
         type = rhs.type;
      }

      return (*this);
   }
};
