#pragma once

#include "Messaging.hpp"
#include "TimerListener.hpp"

class Timer
{

public:

   enum TimerType
   {
      ONE_SHOT,
      PERIODIC
   };

   static void setup(
      const int& numberOfTimers);

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

   static void allocate(
      const int& numberOfTimers);

   static Timer* getFreeTimer();

   Timer();

   void update();

   void expire();

   static Timer* timers;

   static int numberOfTimers;

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
