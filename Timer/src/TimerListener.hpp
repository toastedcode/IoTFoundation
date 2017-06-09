#pragma once

class Timer;

class TimerListener
{

public:

   virtual ~TimerListener() = 0;

   virtual void timeout(
      Timer* timer) = 0;
};

inline TimerListener::~TimerListener() {}
