#include "Timer.h"

Timer::Timer()
{
   isRunning        = false;
   startClock_      = 0;
   startTime_       = 0;
   accumulatedTime_ = 0;
}

double
Timer::getElapsedTime()
{
   time_t accumulatedSeconds = time(0) - startTime_;

   if (accumulatedSeconds < 3600)
      return (clock() - startClock_) / (1.0 * CLOCKS_PER_SEC) * 1000.0;

   else
      return (1.0 * accumulatedSeconds) * 1000.0;
}

void
Timer::start()
{
   if (isRunning)
      return;

   isRunning   = true;
   startClock_ = clock();
   startTime_  = time(0);
}

void
Timer::reset()
{
   isRunning           = false;
   accumulatedTime_    = 0;
   startClock_         = 0;
   startTime_          = 0;
}

void
Timer::stop()
{
   if (isRunning)
      accumulatedTime_ += getElapsedTime();

   isRunning  = false;
}
