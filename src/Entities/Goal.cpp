#include "Goal.h"
#include "../Game/Camera.h"

void
Goal::render(WINDOW* window,
             Camera* camera)
{
   //mvwaddstr(window, (int)position_.y - camera->getY(), (int)position_.x - camera->getX(), "GG");
   //mvwaddstr(window, (int)position_.y + 1 - camera->getY(), (int)position_.x - camera->getX(), "GG");
   mvwaddch(window, (int)position_.y - camera->getY(), (int)position_.x - camera->getX(), ACS_BOARD);
   mvwaddch(window, (int)position_.y - camera->getY() + 1, (int)position_.x - camera->getX(), ACS_BOARD);
   mvwaddch(window, (int)position_.y - camera->getY(), (int)position_.x - camera->getX() + 1, ACS_BOARD);
   mvwaddch(window, (int)position_.y - camera->getY() + 1, (int)position_.x - camera->getX() + 1, ACS_BOARD);
}

Rect
Goal::getBoundingBox()
{
   return Rect(position_.x, position_.y, position_.x + 1.0f, position_.y + 1.0f);
}

std::string
Goal::getDescription()
{
   return "The player wins the level when he touches this. Only put one of this in a level!";
}
