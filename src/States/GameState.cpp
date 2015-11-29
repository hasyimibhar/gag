#include <curses.h>

#include "../Application/Application.h"
#include "GameState.h"
#include "../Common/ColorPairManager.h"
#include "../Game/GameContent.h"
#include "../Game/LevelManager.h"
#include "../Game/LevelTimeManager.h"
#include "../Game/Level.h"
#include "../Common/Common.h"
#include "../Common/Log.h"
#include "../Game/TextInput.h"

#include "../Entities/Player.h"
#include "../Entities/Bullet.h"
#include "../Entities/FirePower.h"

GameState::GameState(Application* host) : State(host)
{
   new TextInput();
   nodelay(host_->getWindow(), true);

   hud_ = subwin(host_->getWindow(), 2, COLS, LINES - 2, 0);

   if (hud_ == 0)
   {
      Log::getInstance().write("Failed to create HUD window!");
      host_->finish(1);
   }
   else
   {
      wbkgd(hud_, COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_MAGENTA, COLOR_WHITE)));

      Player* player = new Player();
      GameContent::getInstance().setPlayer(player);
      GameContent::getInstance().getWorld()->add(player);
      player->setPosition(GameContent::getInstance().getPlayerSpawnPoint());

      GameContent::getInstance().startGameTime();
   }
}

GameState::~GameState()
{
   delwin(hud_);
   delete TextInput::getInstancePointer();
   nodelay(host_->getWindow(), false);
}

void
GameState::update()
{
   int key = wgetch(host_->getWindow());
   TextInput::getInstance().update(key);

   std::vector<Entity*>& updates = GameContent::getInstance().getWorld()->getIndex(ID("updt"));

   FOREACH(vector, Entity*, e, updates)
      (*e)->update();

   Player* player = static_cast<Player*>(GameContent::getInstance().getWorld()->getEntity(ID("plyr")));

   if (player != 0)
      GameContent::getInstance().getCamera()->followEntity(player, -50, -30);

   if (player == 0 && key == '\n')
   {
      if (GameContent::getInstance().getPlayerLives() != 0)
         Application::getInstance().setNextState(STATE_GAME);

      else
         Application::getInstance().setNextState(STATE_CREDITS);
   }

   if (player != 0 && TextInput::getInstance().getText() == "harakiri")
   {
      TextInput::getInstance().clearText();
      player->discard();
   }

   if (player != 0 && TextInput::getInstance().getText() == "jump")
   {
      TextInput::getInstance().clearText();
      player->jump();
   }

   if (player != 0 && !player->getBoundingBox().collide(Rect(0, 0, Level::LEVEL_WIDTH, Level::LEVEL_HEIGHT)))
   {
      player->discard();
   }

   else if (player != 0 && TextInput::getInstance().getText() == "fire")
   {
      TextInput::getInstance().clearText();
      GameContent::getInstance().getWorld()->add(new Bullet((int)player->getX() + 3, (int)player->getY(), Vec(0.5f, 0.0f)));
   }

   else if (player != 0 && TextInput::getInstance().getText() == "burnburnburn")
   {
      TextInput::getInstance().clearText();
      GameContent::getInstance().getWorld()->add(new FirePower());
   }

   /*
   else if (TextInput::getInstance().getText() == "iwanttogotothenextlevel")
   {
      TextInput::getInstance().clearText();
      GameContent::getInstance().setLevelOver(true);
   }
   */

   GameContent::getInstance().getWorld()->reindex();

   if (GameContent::getInstance().isLevelOver())
   {
      char messageBuffer[MAX_MESSAGEBOX_COLS];
      double timeTaken = GameContent::getInstance().getElapsedGameTime();
      sprintf(messageBuffer, "Time taken: %.2f seconds", timeTaken/1000.0f);
      MessageBox(host_->getWindow(), "Victory", messageBuffer);
      GameContent::getInstance().stopGameTime();

      LevelTime* levelTime = new LevelTime();
      levelTime->user = "Anonymous";
      levelTime->time = 999999.0f;

      if (LevelTimeManager::getInstance().getLevelTime(GameContent::getInstance().getCurrentLevel()) != 0)
      {
         levelTime = LevelTimeManager::getInstance().getLevelTime(GameContent::getInstance().getCurrentLevel());
      }

      sprintf(messageBuffer, "Current best time: %.2f seconds by %s", levelTime->time/1000.0f, levelTime->user.c_str());
      MessageBox(host_->getWindow(), "Victory", messageBuffer);

      if (timeTaken < levelTime->time)
      {
         string name = StringBox(host_->getWindow(), "Victory", "You just beat the current best time! Please enter your name: ", 16);
         LevelTimeManager::getInstance().addLevelTime(GameContent::getInstance().getCurrentLevel(), name, timeTaken);
      }

      if (GameContent::getInstance().isTestMode())
         host_->setNextState(STATE_EDITOR);

      else
      {
         GameContent::getInstance().popLevel();

         if (!GameContent::getInstance().getCurrentLevel().empty())
         {
            if (!GameContent::getInstance().setupGame(GameContent::getInstance().getCurrentLevel()))
            {
               MessageBox(host_->getWindow(), "Testing level", "This level does not have a player spawn point! NOOB!");
               nodelay(host_->getWindow(), false);
               Log::getInstance().write("Failed to setup game.");
            }
            else
            {
               //GameContent::getInstance().setPlayerLives(5);

               GameContent::getInstance().setTestMode(false);
               host_->setNextState(STATE_GAME);
            }
         }
         else
         {
            host_->setNextState(STATE_CREDITS);
         }
      }
   }

   if (key == 27)
   {
      if (!GameContent::getInstance().isTestMode()
          && ConfirmBox(host_->getWindow(), "Quit", "Are you sure you want to exit the game?"))
      {
         host_->setNextState(STATE_MAINMENU);
         delete GameContent::getInstancePointer();
         new GameContent();
      }
      else
      {
         host_->setNextState(STATE_EDITOR);
      }
   }

   std::vector<Entity*>& coll1 = GameContent::getInstance().getWorld()->getIndex(ID("coll"));
   std::vector<Entity*>& coll2 = GameContent::getInstance().getWorld()->getIndex(ID("coll"));

   FOREACH(vector, Entity*, e, coll1)
   {
      FOREACH(vector, Entity*, f, coll2)
      {
         if ((*e) != (*f) &&
             (*e)->getBoundingBox().collide((*f)->getBoundingBox()))
         {
            (*e)->handleCollision(*f);
            (*f)->handleCollision(*e);
         }
      }
   }

   GameContent::getInstance().getWorld()->reindex();
}

void
GameState::render()
{
   wclear(host_->getWindow());

   std::vector<Entity*> renders =
      GameContent::getInstance().getCamera()->getEntitiesInView(
         GameContent::getInstance().getWorld(),
         ID("rndr"));

   FOREACH(vector, Entity*, e, renders)
      (*e)->render(host_->getWindow(), GameContent::getInstance().getCamera());

   std::vector<Entity*> powers = GameContent::getInstance().getWorld()->getIndex(ID("powr"));
   FOREACH(vector, Entity*, e, powers)
      (*e)->render(host_->getWindow(), 0);

   TextInput::getInstance().render(host_->getWindow());

   wclear(hud_);
   wborder(hud_, 442, 442, 461, ' ', 457, 443, 442, 442);

   for (int i = 0; i < GameContent::getInstance().getPlayerLives(); i++)
      mvwaddch(hud_, 1, 3 + i, 259);

   wrefresh(host_->getWindow());
}
