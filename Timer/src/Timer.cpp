#include "Board.hpp"
#include "Timer.hpp"

// *****************************************************************************
//                              Public (static)
// *****************************************************************************

Timer Timer::timers[MAX_TIMERS];

Timer* Timer::newTimer(
   const String& id,
   const int& period,
   const TimerType& type)
{
   Timer* timer = getFreeTimer();

   if (timer)
   {
      timer->id = id;
      timer->period = period;
      timer->type = type;
      timer->message = 0;
      timer->listener = 0;
      timer->inUse = true;
      timer->startTime = 0;
      timer->expireTime = 0;
   }

   return (timer);
}

Timer* Timer::newTimer(
   const String& id,
   const int& period,
   const TimerType& type,
   Message* message)
{
   Timer* timer = getFreeTimer();

   if (timer)
   {
      timer->id = id;
      timer->period = period;
      timer->type = type;
      timer->message = message;
      timer->listener = 0;
      timer->inUse = true;
      timer->startTime = 0;
      timer->expireTime = 0;
   }

   return (timer);
}

Timer* Timer::newTimer(
   const String& id,
   const int& period,
   const TimerType& type,
   TimerListener* listener)
{
   Timer* timer = getFreeTimer();

   if (timer)
   {
      timer->id = id;
      timer->period = period;
      timer->type = type;
      timer->message = 0;
      timer->listener = listener;
      timer->inUse = true;
      timer->startTime = 0;
      timer->expireTime = 0;
   }

   return (timer);
}

void Timer::freeTimer(
   Timer* timer)
{
   if (timer)
   {
      timer->id = "";
      timer->period = 0;
      timer->type = ONE_SHOT;
      timer->message = 0;
      timer->listener = 0;
      timer->inUse = false;
      timer->startTime = 0;
      timer->expireTime = 0;
   }
}


void Timer::loop()
{
   for (int i = 0; i < MAX_TIMERS; i++)
   {
      Timer& timer = timers[i];

      if (timer.inUse == true)
      {
         timer.update();
      }
   }
}

// *****************************************************************************
//                                  Public
// *****************************************************************************

Timer::~Timer() {}

void Timer::start()
{
   if (inUse == true)
   {
      reset();
   }
}

void Timer::stop()
{
   if (inUse == true)
   {
      startTime = 0;
      expireTime = 0;
   }
}

void Timer::reset()
{
   if (inUse == true)
   {
      Board* board = Board::getBoard();

      if (board)
      {
         startTime = board->systemTime();
         expireTime = (startTime + period);
      }
   }
}

bool Timer::isStarted() const
{
   return (inUse && (startTime != 0));
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

Timer* Timer::getFreeTimer()
{
   Timer* freeTimer = 0;

   for (int i = 0; i < MAX_TIMERS; i++)
   {
      if (timers[i].inUse == false)
      {
         freeTimer = &(timers[i]);
         break;
      }
   }

   return (freeTimer);
}

Timer::Timer() : id(""),
                 period(0),
                 type(ONE_SHOT),
                 message(0),
                 listener(0),
                 inUse(false),
                 startTime(0),
                 expireTime(0)
{
}

void Timer::update()
{
   if (isStarted() && !isExpired())
   {
      Board* board = Board::getBoard();

      if (board)
      {
         unsigned long currentTime = board->systemTime();

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

   if (isStarted() && (type == PERIODIC))
   {
      reset();
   }
   else
   {
      freeTimer(this);
   }
}
