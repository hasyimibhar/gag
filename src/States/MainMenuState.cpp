#include "../Application/Application.h"
#include "MainMenuState.h"
#include "../Common/Common.h"
#include "../Common/Log.h"
#include "../Game/GameContent.h"

MainMenuState::MainMenuState(Application* host) : State(host)
{
   delete GameContent::getInstancePointer();
   new GameContent();

   options_.push_back("Start game");
   options_.push_back("Level editor");
   //options_.push_back("View highscores");
   options_.push_back("View credits");
   options_.push_back("Quit game");

   iOption_ = 0;

   nodelay(host_->getWindow(), true);
}

MainMenuState::~MainMenuState()
{
   nodelay(host_->getWindow(), false);
}

void
MainMenuState::update()
{
   int key = wgetch(host_->getWindow());

   if (key == KEY_UP && iOption_ > 0)
      iOption_--;

   if (key == KEY_DOWN && iOption_ < (int)options_.size() - 1)
      iOption_++;

   if (key == '\n')
   {
      switch (iOption_)
      {
         case 0 :
            GameContent::getInstance().addLevel("levels/Level 4.lvl");
            GameContent::getInstance().addLevel("levels/Level 3.lvl");
            GameContent::getInstance().addLevel("levels/Level 2.lvl");
            GameContent::getInstance().addLevel("levels/Level 1.lvl");
            GameContent::getInstance().addLevel("levels/tutorial.lvl");

            if (!GameContent::getInstance().setupGame(GameContent::getInstance().getCurrentLevel()))
            {
               MessageBox(host_->getWindow(), "Testing level", "This level does not have a player spawn point! NOOB!");
               nodelay(host_->getWindow(), false);
               Log::getInstance().write("Failed to setup game.");
            }
            else
            {
               GameContent::getInstance().setPlayerLives(5);
               GameContent::getInstance().setTestMode(false);

               host_->setNextState(STATE_GAME);
            }
         break;

         case 1 :
            host_->setNextState(STATE_EDITOR);
         break;

         case 2 :
            host_->setNextState(STATE_CREDITS);
         break;

         case 3 :
            if (ConfirmBox(host_->getWindow(), "Quit", "Are you sure you want to exit the program?"))
               host_->finish(0);
         break;

         default :
         break;
      }
   }

   if (key == 27 &&
       ConfirmBox(host_->getWindow(), "Quit", "Are you sure you want to exit the program?"))
      host_->finish(0);
}

void
MainMenuState::render()
{
   wclear(host_->getWindow());

   int y = 0;

   for (std::list<std::string>::iterator i = options_.begin(); i != options_.end(); i++, y++)
   {
      if (y == iOption_)
         wattron(host_->getWindow(), A_REVERSE);

      mvwaddstr(host_->getWindow(), MAIN_MENU_Y + y * 2, MAIN_MENU_X, (*i).c_str());

      if (y == iOption_)
         wattroff(host_->getWindow(), A_REVERSE);
   }
}
