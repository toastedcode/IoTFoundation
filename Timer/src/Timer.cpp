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
         timers.remove(timer);
         delete (timer);
      }
   }
}

Timer* Timer::newTimer(
   int period,
   TimerType type)
{
   Timer* timer = new Timer(period, type);
   timers.add(timer);

   return (timer);
}

Timer* Timer::newTimer(
   int period,
   TimerType type,
   Message* message)
{
   Timer* timer = new Timer(period, type, message);
   timers.add(timer);

   return (timer);
}

Timer* Timer::newTimer(
   int period,
   TimerType type,
   TimerListener* listener)
{
   Timer* timer = new Timer(period, type, listener);
   timers.add(timer);

   return (timer);
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

bool Timer::isExpired() const
{
   return ((startTime != 0) &&
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
   int period,
   TimerType type) : period(period),
                     type(type),
                     message(message),
                     listener(0),
                     startTime(0),
                     expireTime(0)
{
}

Timer::Timer(
   int frequency,
   TimerType type,
   MessagePtr message) : period(period),
                         type(type),
                         message(message),
                         listener(0),
                         startTime(0),
                         expireTime(0)
{
}

Timer::Timer(
   int frequency,
   TimerType type,
   TimerListener* listener) : period(period),
                              type(type),
                              message(message),
                              listener(0),
                              startTime(0),
                              expireTime(0)
{
}

void Timer::update()
{
   if (isExpired() == false)
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
