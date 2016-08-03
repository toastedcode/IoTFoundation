// *****************************************************************************
// *****************************************************************************
// Address.cpp
//
// Author: Jason Tost
// Date:   7.5.2016
//
// *****************************************************************************
// *****************************************************************************

#include "Address.hpp"

const String SEPERATOR = ".";

void parseAddress(
   const String& address,
   String& location,
   String& id)
{
   int seperatorPos = address.indexOf(SEPERATOR);

   if (seperatorPos == -1)
   {
      location = address;
      id = "";
   }
   else
   {
      location = address.substring(0, seperatorPos);
      id = address.substring(seperatorPos + 1);
   }
}

Address::Address(
   const String& address)
{
   parseAddress(String(address), location, id);
}

Address::Address(
   const char* address)
{
   parseAddress(String(address), location, id);
}

Address& Address::operator=(const Address& rhs)
{
   if (this != &rhs)
   {
      location = rhs.location;
      id = rhs.id;
   }

   return (*this);
}

String Address::toString() const
{
   String address = location;
   if (id != "")
   {
      address += SEPERATOR + id;
   }

   return (address);
}
