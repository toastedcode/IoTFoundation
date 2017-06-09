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

// A character used in separating a message handler id from extra routing information.
//Ex: updHander@10.4.41.179:8080
static const String MESSAGE_HANDLER_ID_SEPARATOR = "@";

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
