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

// Uncomment to enable messaging debugging.
//#define MESSAGING_DEBUG

typedef String MessageId;

typedef String HandlerId;

typedef String Topic;

// A character used in separating a message handler id from extra routing information.
//Ex: updHander@10.4.41.179:8080
static const String MESSAGE_HANDLER_ID_SEPARATOR = "@";

// Message parameter names.
static const char PROGMEM MESSAGE_ID[] = "messageId";
static const char PROGMEM TOPIC[] = "topic";
static const char PROGMEM SOURCE[] = "source";
static const char PROGMEM DESTINATION[] = "destination";
static const char PROGMEM ACTION[] = "action";
static const char PROGMEM INSTRUCTION[] = "instruction";
