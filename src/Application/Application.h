#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <curses.h>

#include "../Common/Singleton.h"
#include "State.h"
#include "../Common/Timer.h"

class Application : public Singleton<Application>
{
   public:
      Application();
      ~Application();

      bool start();
      void run();
      void stop();

      void finish(int);

      void setNextState(StateID);
      void changeState();

      WINDOW* getWindow();

   private:
      WINDOW* window_;

      bool isRunning_;
      int  result_;
      char character_;

      State*  currentState_;
      StateID iCurrentState_;
      StateID iNextState_;

      Timer timer;
};

#endif // APPLICATION_H_INCLUDED
