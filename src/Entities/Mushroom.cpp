#include "Mushroom.h"
#include "Bullet.h"
#include "Player.h"
#include "../Game/GameContent.h"
#include "../Application/Application.h"

Mushroom::Mushroom(Direction direction) : direction_(direction)
{
   velocity_ = Vec(0.0, 0.0);
}

void
Mushroom::update()
{
   if (direction_ == DIR_LEFT)
      velocity_.x = -1 * WALK_SPEED;

   else
      velocity_.x = WALK_SPEED;

   position_ += velocity_;

   if (direction_ == DIR_LEFT &&
       (GameContent::getInstance().getLevel()->getTile((int)position_.x - 1, (int)position_.y + 1) != 0 ||
        GameContent::getInstance().getLevel()->getTile((int)position_.x - 1, (int)position_.y + 2) == 0))
   {
      direction_ = DIR_RIGHT;
   }

   if (direction_ == DIR_RIGHT &&
       (GameContent::getInstance().getLevel()->getTile((int)position_.x + 1, (int)position_.y + 1) != 0 ||
       GameContent::getInstance().getLevel()->getTile((int)position_.x + 1, (int)position_.y + 2) == 0))
   {
      direction_ = DIR_LEFT;
   }
}

void
Mushroom::render(WINDOW* window,
                 Camera* camera)
{
   mvwaddstr(window, (int)position_.y - camera->getY(), (int)position_.x - camera->getX(), "xx");
   mvwaddstr(window, (int)position_.y + 1 - camera->getY(), (int)position_.x - camera->getX(), "xx");
}

Rect
Mushroom::getBoundingBox()
{
   return Rect(position_.x, position_.y, position_.x + 1, position_.y + 1);
}

void
Mushroom::handleCollision(Entity* entity)
{
   Bullet* bullet = dynamic_cast<Bullet*>(entity);
   Player* player = dynamic_cast<Player*>(entity);

   if (bullet != 0)
      discard();

   if (player != 0)
   {
      player->discard();
   }
}

std::string
Mushroom::getDescription()
{
   return "An mushroom. It moves left to right, and cannot be touched by the player.";
}
