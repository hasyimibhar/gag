#include "InfoPopup.h"
#include "../Common/ColorPairManager.h"
#include "../Common/Common.h"
#include "../Common/Log.h"
#include "../Game/Camera.h"
#include "Player.h"
#include "../Application/Application.h"

InfoPopup::InfoPopup(std::string text)
{
   for (int i = 0; i < MAX_TEXT_LENGTH + 1; i++)
      text_[i] = '\0';

   setText(text);
   isTouched_ = false;
}

void
InfoPopup::render(WINDOW* window,
                         Camera* camera)
{
   wattron(window,
           COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_BLACK, COLOR_WHITE)));

   mvwaddch(window, (int)position_.y - camera->getY(), (int)position_.x - camera->getX(), '?');

   wattroff(window,
           COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_BLACK, COLOR_WHITE)));
}

Rect
InfoPopup::getBoundingBox()
{
   return Rect(position_.x, position_.y, position_.x, position_.y);
}

std::string
InfoPopup::getDescription()
{
   return "A bunch of text will pop up when the player touches this thingimmajig.";
}

void
InfoPopup::handleCollision(Entity* entity)
{
   Player* player = dynamic_cast<Player*>(entity);

   if (player != 0 && !isTouched_)
   {
      isTouched_ = true;
      MessageBox(Application::getInstance().getWindow(), "Info", text_);
      discard();
   }
}

void
InfoPopup::save(std::ofstream& file)
{
   Entity::save(file);

   int i;
   for (i = 0; text_[i] != '\0'; i++)
      saveByte(file, text_[i]);

   //Log::getInstance().write("Saved %d characters!", i);

   saveByte(file, '\0');
}

void
InfoPopup::load(std::ifstream& file)
{
   Entity::load(file);

   for (int i = 0; i < MAX_TEXT_LENGTH + 1; i++)
      text_[i] = '\0';

   char c = loadByte(file);
   int nCharacters  = 0;

   while (c != '\0')
   {
      //Log::getInstance().write("Loaded: %c.", c);
      text_[nCharacters++] = c;
      c = loadByte(file);
   }

   //Log::getInstance().write("Loaded %d characters!", nCharacters);
   //Log::getInstance().write("Text is now: %s", text_);

   /*
   for (int i = 0; i < MAX_TEXT_LENGTH; i++)
   {
      char c = loadByte(file);
      text_[i] = c;
      Log::getInstance().write("Loaded character %c.", c);
   }
   */

   //if (loadByte(file) != '\0')
   //   Log::getInstance().write("Hmm....");
}
