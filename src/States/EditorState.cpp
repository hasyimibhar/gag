#include <curses.h>
#include <fstream>

#include "EditorState.h"
#include "../Application/Application.h"
#include "../Common/Common.h"
#include "../Common/Log.h"
#include "../Game/LevelManager.h"
#include "../Game/GameContent.h"

#include "../Entities/Tile.h"
#include "../Entities/PlayerSpawnPoint.h"
#include "../Entities/PlayerCheckPoint.h"
#include "../Entities/Mushroom.h"
#include "../Entities/Goal.h"
#include "../Entities/Spike.h"
#include "../Entities/InfoPopup.h"

EditorState::EditorState(Application* host) : State(host), pX_(0), pY_(0), selected_(0)
{
   for (int i = 0; i < Level::LEVEL_HEIGHT; i++)
      for (int j = 0; j < Level::LEVEL_WIDTH; j++)
         entities_[i][j] = 0;

   pallete_.push_back(new PlayerSpawnPoint());
   pallete_.push_back(new PlayerCheckPoint());
   pallete_.push_back(new Goal());

   pallete_.push_back(new Tile(ACS_BLOCK,   COLOR_RED, COLOR_YELLOW, 0, 0, 0));
   pallete_.push_back(new Tile(ACS_CKBOARD, COLOR_RED, COLOR_YELLOW, 0, 0, 0));
   pallete_.push_back(new Tile(ACS_BOARD,   COLOR_RED, COLOR_YELLOW, 0, 0, 0));

   pallete_.push_back(new Tile(ACS_BLOCK,   COLOR_BLUE, COLOR_WHITE, 0, 0, 0));
   pallete_.push_back(new Tile(ACS_CKBOARD, COLOR_BLUE, COLOR_WHITE, 0, 0, 0));
   pallete_.push_back(new Tile(ACS_BOARD,   COLOR_BLUE, COLOR_WHITE, 0, 0, 0));

   pallete_.push_back(new Mushroom(Mushroom::DIR_LEFT));

   pallete_.push_back(new Spike());
   pallete_.push_back(new InfoPopup("Hello world! You just wasted 3 seconds of your life reading this."));

   for (std::vector<Entity*>::iterator i = pallete_.begin(); i != pallete_.end(); i++)
   {
      (*i)->setPosition(Vec(3, LINES - 4));
   }

   curs_set(2);
   //nodelay(host_->getWindow(), true);

   dummy = new Camera(0, 0);

   isAutoPutOn_ = false;
   isPanningModeOn_ = false;
   isModified_  = false;

   if (!GameContent::getInstance().getCurrentLevel().empty())
   {
      currentFileName_ = GameContent::getInstance().getCurrentLevel();
      delete GameContent::getInstancePointer();
      new GameContent();

      LevelManager::getInstance().load(currentFileName_.c_str(), GameContent::getInstance().getWorld());
      GameContent::getInstance().getWorld()->reindex();

      std::vector<Entity*>& loads = GameContent::getInstance().getWorld()->getIndex(ID("entt"));
      FOREACH(vector, Entity*, e, loads)
      {
         entities_[(int)(*e)->getY()][(int)(*e)->getX()] = (*e);
      }
   }

   clipboard_ = 0;

   //Log::getInstance().write("I'm here!!!");
}

EditorState::~EditorState()
{
   for (int i = 0; i < Level::LEVEL_HEIGHT; i++)
      for (int j = 0; j < Level::LEVEL_WIDTH; j++)
         delete entities_[i][j];

   //nodelay(host_->getWindow(), false);
   curs_set(0);

   delete dummy;
}

void
EditorState::update()
{
   flushinp();
   int input = wgetch(host_->getWindow());

   if (input == KEY_LEFT)
   {
      if (isPanningModeOn_)
         pX_ -= 10;
      else
         pX_--;
   }

   if (input == KEY_RIGHT)
   {
      if (isPanningModeOn_)
         pX_ += 10;
      else
         pX_++;
   }

   if (input == KEY_UP)
   {
      if (isPanningModeOn_)
         pY_ -= 10;
      else
         pY_--;
   }

   if (input == KEY_DOWN)
   {
      if (isPanningModeOn_)
         pY_ += 10;
      else
         pY_++;
   }

   if (pX_ < 0)
      pX_ = 0;

   if (pX_ >= Level::LEVEL_WIDTH - 1)
      pX_ = Level::LEVEL_WIDTH - 1;

   if (pY_ < 0)
      pY_ = 0;

   if (pY_ >= Level::LEVEL_HEIGHT - 1)
      pY_ = Level::LEVEL_HEIGHT - 1;

   if (input == KEY_HOME)
      pX_ = 0;

   if (input == KEY_END)
      pX_ = Level::LEVEL_WIDTH - 1;

   if (input == KEY_PPAGE)
      pY_ = 0;

   if (input == KEY_NPAGE)
      pY_ = Level::LEVEL_HEIGHT - 1;

   if (input == 'q')
   {
      if (selected_ > 0)
         selected_--;

      else
         selected_ =  (int)pallete_.size() - 1;
   }

   if (input == 'w')
   {
      if (selected_ < (int)pallete_.size() - 1)
         selected_++;

      else
         selected_ = 0;
   }

   if (input == '\t')
   {
      isAutoPutOn_ = !isAutoPutOn_;
   }

   if (input == 'z')
   {
      isPanningModeOn_ = !isPanningModeOn_;
   }

   if (isAutoPutOn_ || input == '\n')
   {
      if (entities_[pY_][pX_] != 0)
      {
         GameContent::getInstance().getWorld()->remove(entities_[pY_][pX_]);
      }

      Entity* toPut = pallete_[selected_]->getClone();
      toPut->setPosition(Vec(pX_, pY_));
      GameContent::getInstance().getWorld()->add(toPut);
      GameContent::getInstance().getWorld()->reindex();
      entities_[pY_][pX_] = toPut;
      isModified_ = true;

      InfoPopup* infoPopup = dynamic_cast<InfoPopup*>(toPut);

      if (infoPopup != 0)
      {
         std::string text = StringBox(host_->getWindow(),
                                      "Information popup text",
                                      "Enter the text to be displayed :",
                                      InfoPopup::MAX_TEXT_LENGTH);
         infoPopup->setText(text);
      }

      Log::getInstance().write("Placed entity at location: %.3f, %.3f", toPut->getX(), toPut->getY());
   }

   if (input == 'r')
   {
      if (entities_[pY_][pX_] != 0)
      {
         GameContent::getInstance().getWorld()->remove(entities_[pY_][pX_]);
         GameContent::getInstance().getWorld()->reindex();
         entities_[pY_][pX_] = 0;
         Log::getInstance().write("Removed a tile at %d, %d", pX_, pY_);
         isModified_ = true;
      }
   }

   if (input == 'c')
   {
      if (entities_[pY_][pX_] != 0)
      {
         if (clipboard_ != 0)
            delete clipboard_;

         clipboard_ = entities_[pY_][pX_]->getClone();
      }
   }

   if (input == 'v')
   {
      if (entities_[pY_][pX_] != 0)
      {
         GameContent::getInstance().getWorld()->remove(entities_[pY_][pX_]);
      }

      Entity* toPut = clipboard_->getClone();
      toPut->setPosition(Vec(pX_, pY_));
      GameContent::getInstance().getWorld()->add(toPut);
      GameContent::getInstance().getWorld()->reindex();
      entities_[pY_][pX_] = toPut;
      isModified_ = true;
   }

   if (input == 'o')
   {
      //GameContent::getInstance().getWorld()->setBestUser("Anonymous");
      //GameContent::getInstance().getWorld()->setBestTime(999999.0f);
   }

   if (input == 's' || input == 'd')
   {
      bool isFirstTime = false;

      if (input == 'd' || currentFileName_.empty())
      {
         isFirstTime = true;
         currentFileName_ = StringBox(host_->getWindow(), "Saving level", "Enter the file name for this level :", 25);
      }

      if (!currentFileName_.empty())
      {
         if (isFirstTime)
            currentFileName_ += ".lvl";

         bool shouldSave = true;

         if (std::ifstream(currentFileName_.c_str()))
         {
            shouldSave = ConfirmBox(host_->getWindow(), "Saving level", "A level with that file name exists. Overwrite?");
         }

         if (shouldSave)
         {
            LevelManager::getInstance().save(currentFileName_, GameContent::getInstance().getWorld());
            MessageBox(host_->getWindow(), "Saving level", "Your level has been saved! Yay :D");
            nodelay(host_->getWindow(), false);
            isModified_ = false;
         }
         else
         {
            currentFileName_.clear();
         }
      }
   }

   if (input == 'l')
   {
      currentFileName_ = StringBox(host_->getWindow(), "Load level", "Enter the file name of the level :", 25);
      //string fileName = StringBox(host_->getWindow(), "Load level", "Enter the file name of the level :", 25);

      if (!currentFileName_.empty())
      {
         currentFileName_ += ".lvl";

         if (!std::ifstream(currentFileName_.c_str()))
         {
            MessageBox(host_->getWindow(), "Loading level", "Could not find the file!");
            nodelay(host_->getWindow(), false);
            currentFileName_.clear();
         }
         else
         {
            std::vector<Entity*>& entities = GameContent::getInstance().getWorld()->getIndex(ID("entt"));

            FOREACH(vector, Entity*, e, entities)
               GameContent::getInstance().getWorld()->remove(*e);

            GameContent::getInstance().getWorld()->reindex();

            for (int i = 0; i < Level::LEVEL_HEIGHT; i++)
               for (int j = 0; j < Level::LEVEL_WIDTH; j++)
                  entities_[i][j] = 0;

            LevelManager::getInstance().load(currentFileName_.c_str(), GameContent::getInstance().getWorld());
            GameContent::getInstance().getWorld()->reindex();

            std::vector<Entity*>& loads = GameContent::getInstance().getWorld()->getIndex(ID("entt"));
            FOREACH(vector, Entity*, e, loads)
            {
               //Log::getInstance().write("Accessing float %.3f, %.3f.", (*e)->getX(), (*e)->getY());
               //Log::getInstance().write("Accessing int %d, %d.", (int)(*e)->getX(), (int)(*e)->getY());
               entities_[(int)(*e)->getY()][(int)(*e)->getX()] = (*e);
            }

            MessageBox(host_->getWindow(), "Loading level", "Here you go. Level loaded. -___-");
            nodelay(host_->getWindow(), false);
            isModified_ = false;
         }
      }
   }

   if (input == 't' && !currentFileName_.empty())
   {
      LevelManager::getInstance().save(currentFileName_, GameContent::getInstance().getWorld());
      MessageBox(host_->getWindow(), "Saving level", "Your level has been saved! Now let's test it...");
      nodelay(host_->getWindow(), false);
      isModified_ = false;

      if (!GameContent::getInstance().setupGame(currentFileName_))
      {
         MessageBox(host_->getWindow(), "Testing level", "This level does not have a player spawn point! NOOB!");
         nodelay(host_->getWindow(), false);
         Log::getInstance().write("Failed to setup game.");
      }
      else
      {
         GameContent::getInstance().addLevel(currentFileName_);
         GameContent::getInstance().setPlayerLives(5);
         GameContent::getInstance().setTestMode(true);

         host_->setNextState(STATE_GAME);
      }
   }

   if (input == 27)
   {
      if (isModified_)
      {
         if (ConfirmBox(host_->getWindow(), "Quit", "Do you want to save your level before quitting?"))
         {
            LevelManager::getInstance().save(currentFileName_, GameContent::getInstance().getWorld());
            MessageBox(host_->getWindow(), "Saving level", "Your level has been saved! Yay :D");
            nodelay(host_->getWindow(), false);
         }
      }

      if (ConfirmBox(host_->getWindow(), "Quit", "Are you sure you want to exit the level editor?"))
         host_->setNextState(STATE_MAINMENU);
   }

   GameContent::getInstance().getCamera()->setPosition(pX_ - 30, pY_ - 10);
   GameContent::getInstance().getCamera()->clamp(0, 0, Level::LEVEL_WIDTH, Level::LEVEL_HEIGHT);
}

void
EditorState::render()
{
   wclear(host_->getWindow());

   std::vector<Entity*> renders =
      GameContent::getInstance().getCamera()->getEntitiesInView(
         GameContent::getInstance().getWorld(),
         ID("entt"));

   FOREACH(vector, Entity*, e, renders)
      (*e)->render(host_->getWindow(), GameContent::getInstance().getCamera());

   pallete_[selected_]->render(host_->getWindow(), dummy);

   if (!currentFileName_.empty())
      mvwaddstr(host_->getWindow(), 0, 3, currentFileName_.c_str());


   if (isAutoPutOn_)
      mvwaddstr(host_->getWindow(), 0, 20, "Auto put mode");

   if (isPanningModeOn_)
      mvwaddstr(host_->getWindow(), 0, 40, "Panning mode");

   mvwaddstr(host_->getWindow(), LINES - 4, 7, pallete_[selected_]->getDescription().c_str());

   wmove(host_->getWindow(),
         pY_ - GameContent::getInstance().getCamera()->getY(),
         pX_ - GameContent::getInstance().getCamera()->getX());
}
