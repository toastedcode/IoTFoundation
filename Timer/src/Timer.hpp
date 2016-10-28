#pragma once

#include "Messaging.hpp"
#include "Set.hpp"
#include "TimerListener.hpp"

static const int MAX_TIMERS = 50;

typedef Set<Timer*, MAX_TIMERS> TimerSet;

class Timer
{

public:

   enum TimerType
   {
      ONE_SHOT,
      PERIODIC
   };

   static void setup();

   static void loop();

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

   Timer(
      const String& id,
      const int& period,
      const TimerType& type);

   Timer(
      const String& id,
      const int& period,
      const TimerType& type,
      MessagePtr message);

   Timer(
      const String& id,
      const int& period,
      const TimerType& type,
      TimerListener* listener);

   void update();

   void expire();

   static TimerSet timers;

   String id;

   int period;

   TimerType type;

   MessagePtr message;

   TimerListener* listener;

   long startTime;

   long expireTime;
};

inline String Timer::getId() const
{
   return (id);
}
