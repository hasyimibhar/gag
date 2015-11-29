#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <ctime>

class Timer
{
   public:
      Timer();

      void     start();
      void     reset();
      void     stop();
      double   getElapsedTime();

      bool     isRunning;

   private:
      clock_t  startClock_;
      time_t   startTime_;
      double   accumulatedTime_;
};

#endif // TIMER_H_INCLUDED
