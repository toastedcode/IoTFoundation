#include "Board.hpp"
#include "Timer.hpp"

// *****************************************************************************
//                              Public (static)
// *****************************************************************************

TimerSet Timer::timers;

void Timer::setup() {}

void Timer::loop()
{
   for (int i = 0; i < timers.length(); i++)
   {
      Timer* timer = timers.item(i)->value;

      // Update.
      timer->update();

      // Remove expired timers.
      if  (timer->isExpired())
      {
         freeTimer(timer);
      }
   }
}

Timer* Timer::newTimer(
   const String& id,
   const int& period,
   const TimerType& type)
{
   Timer* timer = new Timer(id, period, type);
   timers.add(timer);

   return (timer);
}

Timer* Timer::newTimer(
   const String& id,
   const int& period,
   const TimerType& type,
   Message* message)
{
   Timer* timer = new Timer(id, period, type, message);
   timers.add(timer);

   return (timer);
}

Timer* Timer::newTimer(
   const String& id,
   const int& period,
   const TimerType& type,
   TimerListener* listener)
{
   Timer* timer = new Timer(id, period, type, listener);
   timers.add(timer);

   return (timer);
}

void Timer::freeTimer(
   Timer* timer)
{
   if (timer)
   {
      timers.remove(timer);
      delete (timer);
   }
}


// *****************************************************************************
//                                  Public
// *****************************************************************************

Timer::~Timer() {}

void Timer::start()
{
   reset();
}

void Timer::stop()
{
   startTime = 0;
   expireTime = 0;
}

void Timer::reset()
{
   if (Board::getBoard())
   {
      startTime = Board::getBoard()->systemTime();
      expireTime = (startTime + period);
   }
}

bool Timer::isStarted() const
{
   return (startTime != 0);
}

bool Timer::isExpired() const
{
   return (isStarted() &&
           (expireTime == 0));
}

void Timer::setMessage(
   MessagePtr message)
{
   if (message)
   {
      message->setFree();
   }

   this->message = message;
}

void Timer::setListener(
   TimerListener* listener)
{
   this->listener = listener;
}

// *****************************************************************************
//                                  Private
// *****************************************************************************

Timer::Timer(
   const String& id,
   const int& period,
   const TimerType& type) : id(id),
                            period(period),
                            type(type),
                            message(0),
                            listener(0),
                            startTime(0),
                            expireTime(0)
{
}

Timer::Timer(
   const String& id,
   const int& period,
   const TimerType& type,
   MessagePtr message) : id(id),
                         period(period),
                         type(type),
                         message(message),
                         listener(0),
                         startTime(0),
                         expireTime(0)
{
}

Timer::Timer(
   const String& id,
   const int& period,
   const TimerType& type,
   TimerListener* listener) : id(id),
                              period(period),
                              type(type),
                              message(0),
                              listener(listener),
                              startTime(0),
                              expireTime(0)
{
}

void Timer::update()
{
   if (isStarted() && !isExpired())
   {
      if (Board::getBoard())
      {
         int currentTime = Board::getBoard()->systemTime();

         if (currentTime > expireTime)
         {
            expire();
         }
      }
   }
}

void Timer::expire()
{
   if (message)
   {
      Messaging::send(Messaging::copyMessage(message));
   }

   if (listener)
   {
      listener->timeout(this);
   }

   if (type == PERIODIC)
   {
      reset();
   }
   else
   {
      expireTime = 0;
   }
}
