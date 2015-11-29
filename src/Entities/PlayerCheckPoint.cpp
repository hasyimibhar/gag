#include <curses.h>

#include "../Game/GameContent.h"
#include "PlayerCheckPoint.h"
#include "../Common/ColorPairManager.h"

PlayerCheckPoint::PlayerCheckPoint()
{
   isTouched_ = false;
}

void
PlayerCheckPoint::render(WINDOW* window,
                         Camera* camera)
{
   wattron(window,
           COLOR_PAIR(ColorPairManager::getInstance().getColorPair((isTouched_ ? COLOR_GREEN : COLOR_RED), COLOR_BLACK)));

   mvwaddch(window, (int)position_.y - camera->getY(), (int)position_.x - camera->getX(), ACS_DIAMOND);

   wattroff(window,
           COLOR_PAIR(ColorPairManager::getInstance().getColorPair((isTouched_ ? COLOR_GREEN : COLOR_RED), COLOR_BLACK)));

   wattron(window,
           COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_YELLOW, COLOR_BLACK)));

   mvwaddch(window, (int)position_.y + 1 - camera->getY(), (int)position_.x - camera->getX(), ACS_TTEE);

   wattroff(window,
           COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_YELLOW, COLOR_BLACK)));
}

Rect
PlayerCheckPoint::getBoundingBox()
{
   return Rect(position_.x, position_.y, position_.x, position_.y + 1);
}

std::string
PlayerCheckPoint::getDescription()
{
   return "After touching this, the player will spawn at this position after death. Cool, huh?";
}

void
PlayerCheckPoint::handleCollision(Entity* entity)
{
   Player* player = dynamic_cast<Player*>(entity);

   if (player != 0 && !isTouched_)
   {
      isTouched_ = true;
      GameContent::getInstance().setPlayerSpawnPoint(getPosition());
   }
}
