#pragma once

#include "Messaging.hpp"
#include "TimerListener.hpp"

class Timer
{

public:

   friend class Pool<Timer>;

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

   typedef Pool<Timer> TimerPool;

   static TimerPool timerPool;

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
