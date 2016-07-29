// *****************************************************************************
// *****************************************************************************
// Address.hpp
//
// Author: Jason Tost
// Date:   6.3.2016
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "MessagingDefs.hpp"

struct Address
{

   Address();

   Address(
      const String& location,
      const String& id);

   Address(
      const String& address);

   Address(
      const char* address);

   bool operator==(const Address& rhs) const;

   bool operator<(const Address& rhs) const;

   Address& operator=(const Address& rhs);

   String toString() const;

   String location;

   String id;
};

inline Address::Address() :
   location(""),
   id("")
{
   // Nothing to do here.
}

inline Address::Address(
   const String& location,
   const String& id) :
      location(location),
      id(id)
{
   // Nothing to do here.
}

inline bool Address::operator==(const Address& rhs) const
{
   return ((location == rhs.location) &&
           (id == rhs.id));
}

inline bool Address::operator<(const Address& rhs) const
{
   return (toString() < rhs.toString());
}
