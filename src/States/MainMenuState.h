#ifndef MAINMENUSTATE_H_INCLUDED
#define MAINMENUSTATE_H_INCLUDED

#include <string>
#include <list>

#include "../Application/State.h"

class MainMenuState : public State
{
   public:
      static const int MAIN_MENU_X      = 30;
      static const int MAIN_MENU_Y      = 15;

      MainMenuState(Application*);
      ~MainMenuState();

      void update();
      void render();

   private:
      std::list<std::string> options_;
      int                    iOption_;
};

#endif // MAINMENUSTATE_H_INCLUDED
