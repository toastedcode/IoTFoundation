#pragma once

#include "Messaging.hpp"
#include "List.hpp"
#include "TimerListener.hpp"

static const int MAX_TIMERS = 50;

class Timer
{

public:

   enum TimerType
   {
      ONE_SHOT,
      PERIODIC
   };

   static Timer* newTimer(
      const String& id,
      const int& period,
      const TimerType& type);

   static Timer* newTimer(
      const String& id,
      const int& period,
      const TimerType& type,
      MessagePtr message);

   static Timer* newTimer(
      const String& id,
      const int& period,
      const TimerType& type,
      TimerListener* listener);

   static void freeTimer(
      Timer* timer);

   static void loop();

   virtual ~Timer();

   String getId() const;

   void start();

   void stop();

   void reset();

   bool isStarted() const;

   bool isExpired() const;

   void setMessage(
      MessagePtr message);

   void setListener(
      TimerListener* listener);

private:

   static Timer* getFreeTimer();

   Timer();

   void update();

   void expire();

   static Timer timers[MAX_TIMERS];

   String id;

   int period;

   TimerType type;

   MessagePtr message;

   TimerListener* listener;

   bool inUse;

   unsigned long startTime;

   unsigned long expireTime;
};

inline String Timer::getId() const
{
   return (id);
}
