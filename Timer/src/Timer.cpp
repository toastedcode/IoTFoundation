#include "Board.hpp"
#include "Logger.hpp"
#include "Timer.hpp"

// *****************************************************************************
//                              Public (static)
// *****************************************************************************

Timer::TimerPool Timer::timerPool(0);

void Timer::setup(
   const int& numberOfTimers)
{
   timerPool.allocate(numberOfTimers);
}


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

      timerPool.setFree(timer);
   }
}


void Timer::loop()
{
   Set<Timer*> inUseSet = timerPool.inUseSet();

   for (Set<Timer*>::Iterator it = inUseSet.begin(); it != inUseSet.end(); it++)
   {
      (*it)->update();
   }
}

// *****************************************************************************
//                                  Public
// *****************************************************************************

Timer::~Timer() {}

void Timer::start()
{
   if (inUse)
   {
      reset();
   }
}

void Timer::stop()
{
   if (inUse)
   {
      startTime = 0;
      expireTime = 0;
   }
}

void Timer::reset()
{
   if (inUse)
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

long Timer::getExpireTime()
{
   long timeToExpiration = 0;

   Board* board = Board::getBoard();

   if (isStarted() && board)
   {
      unsigned long currentTime = board->systemTime();
      timeToExpiration = (expireTime - currentTime);
   }

   return (timeToExpiration);
}

void Timer::setMessage(
   MessagePtr message)
{
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

void Timer::allocate(
   const int& numberOfTimers)
{
   // Create the pool.
   timerPool.allocate(numberOfTimers);
}

Timer* Timer::getFreeTimer()
{
   Timer* freeTimer = timerPool.getFree();

   if (!freeTimer)
   {
      Logger::logSevere(F("Timer::getFreeTimer: Timer pool exhausted."));
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

   if (type == PERIODIC)
   {
      if (isStarted())
      {
         reset();
      }
   }
   else
   {
      freeTimer(this);
   }
}
