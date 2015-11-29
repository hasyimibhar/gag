#include <curses.h>

#include "Application.h"
#include "State.h"
#include "../Common/Log.h"
#include "../Common/ColorPairManager.h"
#include "../Game/LevelManager.h"
#include "../Game/CollisionManager.h"
#include "../Game/GameContent.h"
#include "../Game/LevelTimeManager.h"

#include "../States/NullState.h"
#include "../States/GameState.h"
#include "../States/EditorState.h"
#include "../States/MainMenuState.h"
#include "../States/CreditsState.h"

Application::Application()
{
   initscr();
   resize_term(50, 100);
   window_ = newwin(50, 100, 0, 0);

   if (window_ == 0)
   {
      Log::getInstance().write("Unable to allocate window. Using stdsrc.");
      window_ = stdscr;
   }
   else
   {
      wrefresh(window_);
   }

   noecho();
   curs_set(0);
   keypad(window_, true);
}

Application::~Application()
{
   delwin(window_);
   endwin();
}

bool Application::start()
{
   if (!has_colors())
   {
      Log::getInstance().write("Your terminal does not support color.");
      return false;
   }

   if (start_color() != OK)
   {
      Log::getInstance().write("Failed to initialize color.");
      return false;
   }

   new ColorPairManager();
   new LevelManager();
   new LevelTimeManager();
   new CollisionManager();
   new GameContent();

   LevelTimeManager::getInstance().load();

   //if (!GameContent::getInstance().setupGame("editor.lvl"))
   //   return false;

   //GameContent::getInstance().setPlayerLives(5);

   iCurrentState_ = STATE_MAINMENU;
   iNextState_    = STATE_NULL;
   currentState_  = new MainMenuState(this);

   isRunning_ = true;

   return true;
}

void Application::run()
{
   timer.start();

   while (isRunning_)
   {
      changeState();

      if (timer.getElapsedTime() >= 1000/60)
      {
         timer.reset();
         timer.start();
         currentState_->update();
      }

      currentState_->render();
   }

   Log::getInstance().write("Application ended with result %d", result_);
}

void Application::stop()
{
   delete currentState_;
   delete GameContent::getInstancePointer();
   delete CollisionManager::getInstancePointer();
   delete LevelManager::getInstancePointer();
   delete LevelTimeManager::getInstancePointer();
   delete ColorPairManager::getInstancePointer();
}

void Application::finish(int result)
{
   result_    = result;
   isRunning_ = false;
}

void Application::setNextState(StateID iNextState)
{
   iNextState_ = iNextState;
}

void Application::changeState()
{
   if (iNextState_ != STATE_NULL)
   {
      delete currentState_;

      switch (iNextState_)
      {
         case STATE_MAINMENU :
            currentState_ = new MainMenuState(this);
         break;

         case STATE_CREDITS :
            currentState_ = new CreditsState(this);
         break;

         case STATE_GAME :
            currentState_ = new GameState(this);
         break;

         case STATE_EDITOR :
            currentState_ = new EditorState(this);
         break;

         default :
            currentState_ = new NullState(this);
            Log::getInstance().write("Tried to change to an unhandled state with ID %d", iNextState_);
            finish(2);
         break;
      }

      iCurrentState_ = iNextState_;
      iNextState_    = STATE_NULL;
   }
}

WINDOW*
Application::getWindow()
{
   return window_;
}
