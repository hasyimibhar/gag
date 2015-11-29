#include <typeinfo>
#include <string>
using namespace std;

#include "Bullet.h"
#include "Mushroom.h"
#include "Tile.h"
#include "../Game/GameContent.h"
#include "../Common/ColorPairManager.h"
#include "../Common/Log.h"

Bullet::Bullet(int x,
               int y,
               Vec velocity)
{
   position_.x = x;
   position_.y = y;
   velocity_   = velocity;
   lifeTimer_.start();
}

void
Bullet::update()
{
   position_ += velocity_;

   if (GameContent::getInstance().getLevel()->getTile((int)position_.x - 1, (int)position_.y) != 0 ||
       lifeTimer_.getElapsedTime() >= MAX_LIFE)
   {
      discard();
   }
}

void
Bullet::render(WINDOW* window,
               Camera* camera)
{
   wattron(window, COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_YELLOW, COLOR_BLACK)));
   mvwaddch(window, (int)position_.y - camera->getY(), (int)position_.x - camera->getX(), 271);
   wattroff(window, COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_YELLOW, COLOR_BLACK)));
}

Rect
Bullet::getBoundingBox()
{
   return Rect(position_.x, position_.y, position_.x, position_.y);
}

void
Bullet::handleCollision(Entity* entity)
{
   discard();
}
