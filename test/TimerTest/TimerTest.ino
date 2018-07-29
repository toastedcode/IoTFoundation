#include "Esp8266Board.hpp"
#include "Logger.h"
#include "Timer.h"

class MyTimerListener : public TimerListener
{
   void timeout(
      Timer* timer)
   {
      Logger::logDebug("%s expired\n", timer->getId().c_str());
   }
};


class RestartListener : public TimerListener
{
   void timeout(
      Timer* timer)
   {
      Logger::logDebug("%s expired.\n", timer->getId().c_str());
      
      if (!restartedOnce)
      {
         Logger::logDebug("Restarting\n", timer->getId().c_str());
         
        timer->start();
        restartedOnce = true;
      }
   }

private:

   bool restartedOnce = false;
 };
 
 
MyTimerListener listener;

RestartListener restartListener;
 
void setup()
{
   Serial.begin(9600);
   Logger::setLogger(new SerialLogger());

   Board::setBoard(new Esp8266Board());

   Logger::logDebug("\n\n********** Timer Test **********\n\n");

   Timer::setup(10);
   
   Timer* timer = NULL;

   /*
   for (int i = 0; i < 10; i++)
   {
      String timerId = "myTimer_" + String(i);
      
      timer = Timer::newTimer(
         timerId,
         5000,
         Timer::ONE_SHOT,
         &listener);
         
         timer->start();
   }
   
   // One past our allocated pool size.
   timer = Timer::newTimer(
      "badTimer",
      5000,
      Timer::ONE_SHOT,
      &listener);
   */

     timer = Timer::newTimer(
        "myTimer",
        5000,
        Timer::ONE_SHOT,
        &restartListener);
     
        timer->start();
}

void loop()
{
   Timer::loop();
}
