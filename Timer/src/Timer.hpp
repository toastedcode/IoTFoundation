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
      int period,
      TimerType type);

   static Timer* newTimer(
      int period,
      TimerType type,
      MessagePtr message);

   static Timer* newTimer(
      int period,
      TimerType type,
      TimerListener* listener);

   virtual ~Timer();

   void start();

   void stop();

   void reset();

   bool isExpired() const;

   void setMessage(
      MessagePtr message);

   void setListener(
      TimerListener* listener);

private:

   Timer(
      int period,
      TimerType type);

   Timer(
      int period,
      TimerType type,
      MessagePtr message);

   Timer(
      int period,
      TimerType type,
      TimerListener* listener);

   void update();

   void expire();

   void destroy();

   static TimerSet timers;

   int period;

   TimerType type;

   MessagePtr message;

   TimerListener* listener;

   int startTime;

   int expireTime;
};
