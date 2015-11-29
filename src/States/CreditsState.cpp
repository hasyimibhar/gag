#include "CreditsState.h"
#include "../Application/Application.h"
#include "../Common/ColorPairManager.h"
#include "../Common/Log.h"

CreditsState::CreditsState(Application* host) : State(host)
{
   wclear(host_->getWindow());

   wbkgd(host_->getWindow(),
         COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_BLACK, COLOR_RED)));

   scrollok(host_->getWindow(), true);
   nodelay(host_->getWindow(), true);

   extra_ = subwin(host_->getWindow(), LINES, COLS - 40, 0, 20);

   if (extra_ == 0)
   {
      Log::getInstance().write("Failed to initialize extra credits window.");
      host_->finish(1);
   }

   wbkgd(extra_,
         COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_BLACK, COLOR_WHITE)) | A_BOLD);

   //wrefresh(extra_);

   //int y = LINES - 1;

   //move(LINES - 1, CREDITS_X);

   text_.push_back(";GAG : Group Action Game");
   text_.push_back("A group assignment for C++ Programming II");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back(";PROGRAMMER");
   text_.push_back("");
   text_.push_back("Hasyimi bin Bahrudin a.k.a Fishcake");
   text_.push_back("");
   text_.push_back("");
   text_.push_back(";GAME DESIGNER");
   text_.push_back("");
   text_.push_back("Ryan Wong Wei Yung a.k.a VoDoo");
   text_.push_back("Chai Xinle");
   text_.push_back("");
   text_.push_back("");
   text_.push_back(";LEVEL DESIGNER");
   text_.push_back("");
   text_.push_back("Fishcake - Tutorial level");
   text_.push_back("VoDoo - Level 1 to 4");
   text_.push_back("");
   text_.push_back("");
   text_.push_back(";SPECIAL THANKS TO");
   text_.push_back("");
   text_.push_back("BuZz - For letting us submit really late :P");
   text_.push_back("Limkokwing GHQ - For the nice and free barbeque. Yummeh!");
   text_.push_back("YOU - For playing this game!");
   text_.push_back("");
   text_.push_back(""); // Looping sucks, CTRL-D (CodeBlocks only) is the way to go! :D
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("");
   text_.push_back("Weeee, no more assignments!");
   text_.push_back("You just wasted a few seconds of your life");
   text_.push_back("waiting for this message to come out.");

   scrollY_ = LINES - 1;

   timer_.start();
}

CreditsState::~CreditsState()
{
   wbkgd(host_->getWindow(),
         COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_WHITE, COLOR_BLACK)));

   delwin(extra_);
   scrollok(host_->getWindow(), false);
   nodelay(host_->getWindow(), false);
}

void
CreditsState::update()
{
   int key = wgetch(host_->getWindow());

   if (key == 27)
   {
      host_->setNextState(STATE_MAINMENU);
   }

   if (timer_.getElapsedTime() >= CREDITS_DELAY)
   {
      timer_.reset();
      timer_.start();
      scrollY_--;
   }
}

void
CreditsState::render()
{
   wclear(host_->getWindow());

   wclear(extra_);

   wbkgd(extra_,
         COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_BLACK, COLOR_WHITE)));

   for (int i = 0; i < text_.size(); i++)
   {
      if (!text_[i].empty() && text_[i][0] == ';')
         wattron(extra_,
                 COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_GREEN, COLOR_WHITE)));

      mvwaddstr(extra_, scrollY_ + i, 2, text_[i].c_str());

      if (!text_[i].empty() && text_[i][0] == ';')
         wattroff(extra_,
                 COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_GREEN, COLOR_WHITE)));
   }

   wrefresh(host_->getWindow());
}
