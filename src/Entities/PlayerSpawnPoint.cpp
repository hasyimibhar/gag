#include <curses.h>

#include "PlayerSpawnPoint.h"
#include "../Game/GameContent.h"

void
PlayerSpawnPoint::render(WINDOW* window,
                         Camera* camera)
{
   mvwaddch(window, (int)position_.y - camera->getY(), (int)position_.x - camera->getX(), 399);
}

std::string
PlayerSpawnPoint::getDescription()
{
   return "The spawn point for the player. Only put one of this in a level!";
}

Rect
PlayerSpawnPoint::getBoundingBox()
{
   return Rect(position_.x, position_.y, position_.x, position_.y);
}
