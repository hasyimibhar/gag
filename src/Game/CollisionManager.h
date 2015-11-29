#ifndef COLLISIONMANAGER_H_INCLUDED
#define COLLISIONMANAGER_H_INCLUDED

#include "../Common/Singleton.h"
#include "../Entities/Tile.h"
#include "Level.h"
#include "../Common/Vector2D.h"

class Collision
{
   public:
      enum Direction
      {
         DIR_NONE,
         DIR_UP,
         DIR_DOWN,
         DIR_LEFT,
         DIR_RIGHT
      };

      Direction direction;
      Tile*     tile;
      double    penetration;

      Collision(Direction _direction,
                Tile*     _tile,
                double    _penetration) : direction(_direction), tile(_tile), penetration(_penetration)
      {
      }
};

class CollisionManager : public Singleton<CollisionManager>
{
   public:
      Collision  getCollision(Entity*, Level*);
      void       ejectEntity(Entity*, Collision);
};

#endif // COLLISIONMANAGER_H_INCLUDED
