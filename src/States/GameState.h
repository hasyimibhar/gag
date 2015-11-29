#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include <curses.h>

#include "../Application/State.h"
#include "../Common/Timer.h"

class GameState : public State
{
   public:
      GameState(Application*);
      ~GameState();

      void update();
      void render();

   private:
      WINDOW* hud_;
};

#endif // GAMESTATE_H_INCLUDED
