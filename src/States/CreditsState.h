#ifndef CREDITSSTATE_H_INCLUDED
#define CREDITSSTATE_H_INCLUDED

#include <vector>
#include <string>
#include <curses.h>

#include "../Application/State.h"
#include "../Common/Timer.h"

class CreditsState : public State
{
   public:
      //static const int CREDITS_X       = 20;
      static const int CREDITS_DELAY   = 400;

      CreditsState(Application*);
      ~CreditsState();

      void update();
      void render();

   private:
      Timer timer_;
      std::vector<std::string> text_;
      int scrollY_;
      WINDOW* extra_;

};

#endif // CREDITSSTATE_H_INCLUDED
