#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "../Game/Entity.h"
#include "../Common/Timer.h"

class Bullet : public Entity
{
   public:
      static const int MAX_LIFE     =  2000;

      Bullet(int, int, Vec);

      int*
      getIndices()
      {
         static int indices[] = { ID("entt"), ID("rndr"), ID("updt"), ID("bull"), ID("coll"), 0 };
         return indices;
      }

      int
      getOrder(int index)
      {
         if (index == ID("rndr"))
            return 40;
         else
            return (uintptr_t)this;
      }

      void update();
      void render(WINDOW*, Camera*);

      Rect getBoundingBox();

      void handleCollision(Entity*);

   private:
      Vec   velocity_;
      Timer lifeTimer_;
};

#endif // BULLET_H_INCLUDED
