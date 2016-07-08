// *****************************************************************************
// *****************************************************************************
// MessageHandler.h
//
// Author: Jason Tost
// Date:   5.25.2016
//
// *****************************************************************************
// *****************************************************************************

#pragma once

#include "Message.hpp"

class MessageHandler
{

public:

   virtual Address getAddress() const = 0;

   virtual bool match(
      const Address& address) = 0;

   // This operation retrieves the message id.
   // True is returned if the message was successfully queued.
   virtual bool queueMessage(
      // A pointer to the message that is to be handled.
      MessagePtr message) = 0;
};
