#include "CollisionManager.h"
#include "../Common/Log.h"

Collision
CollisionManager::getCollision(Entity* entity,
                               Level*  level)
{
   Rect      boundingBox = entity->getBoundingBox();
   Collision collision(Collision::DIR_NONE, 0, 1000.0);
   Tile*     tileBuffer;

   tileBuffer = level->getTile((int)boundingBox.bottomCenter().x, (int)boundingBox.bottomCenter().y);
   if (tileBuffer != 0)
   {
      double penetration = (int)tileBuffer->getY() - boundingBox.bottom();

      if (penetration < collision.penetration)
      {
         collision.direction     = Collision::DIR_DOWN;
         collision.tile          = tileBuffer;
         collision.penetration   = penetration;
      }
   }

   tileBuffer = level->getTile((int)boundingBox.topCenter().x, (int)boundingBox.topCenter().y);
   if (tileBuffer != 0)
   {
      double penetration = boundingBox.top() - (int)tileBuffer->getY();

      if (penetration < collision.penetration)
      {
         collision.direction     = Collision::DIR_UP;
         collision.tile          = tileBuffer;
         collision.penetration   = penetration;
      }
   }

   tileBuffer = level->getTile((int)boundingBox.rightCenter().x, (int)boundingBox.rightCenter().y);
   if (tileBuffer != 0)
   {
      double penetration = (int)tileBuffer->getX() - boundingBox.right();

      if (penetration < collision.penetration)
      {
         collision.direction     = Collision::DIR_RIGHT;
         collision.tile          = tileBuffer;
         collision.penetration   = penetration;
      }
   }

   tileBuffer = level->getTile((int)boundingBox.leftCenter().x, (int)boundingBox.leftCenter().y);
   if (tileBuffer != 0)
   {
      double penetration = boundingBox.left() - (int)tileBuffer->getX();

      if (penetration < collision.penetration)
      {
         collision.direction     = Collision::DIR_LEFT;
         collision.tile          = tileBuffer;
         collision.penetration   = penetration;
      }
   }

   if (collision.direction == Collision::DIR_NONE)
      collision.penetration = 0.0;

   //Log::getInstance().write("Final collision: Dir %d, penetration %.05f.", collision.direction, collision.penetration);

   return collision;
}

void
CollisionManager::ejectEntity(Entity*     entity,
                              Collision   collision)
{
   switch (collision.direction)
   {
      case Collision::DIR_UP : entity->setY(entity->getY() + collision.penetration + 0.5f); break;
      case Collision::DIR_DOWN : entity->setY(entity->getY() - collision.penetration - 0.5f); break;
      case Collision::DIR_LEFT : entity->setX(entity->getX() + collision.penetration + 0.5f); break;
      case Collision::DIR_RIGHT : entity->setX(entity->getX() - collision.penetration - 0.5f); break;
      default : break;
   }
}
