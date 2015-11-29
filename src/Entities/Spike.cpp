#include "Spike.h"
#include "Player.h"
#include "../Game/Camera.h"

void
Spike::render(WINDOW* window,
              Camera* camera)
{
   mvwaddch(window, (int)position_.y - camera->getY(), (int)position_.x - camera->getX(), 'A');
}

Rect
Spike::getBoundingBox()
{
   return Rect(position_.x, position_.y, position_.x, position_.y);
}

void
Spike::handleCollision(Entity* entity)
{
   Player* player = dynamic_cast<Player*>(entity);

   if (player != 0)
   {
      player->discard();
   }
}

std::string
Spike::getDescription()
{
   return "Spike. It says \"Don't touch meh!\"";
}

