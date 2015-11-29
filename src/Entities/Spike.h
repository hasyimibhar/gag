#ifndef SPIKE_H_INCLUDED
#define SPIKE_H_INCLUDED

#include "../Game/Entity.h"

class Spike : public Entity
{
   public:

      int*
      getIndices()
      {
         static int indices[] = { ID("entt"), ID("rndr"), ID("coll"), 0 };
         return indices;
      }

      int
      getOrder(int index)
      {
         if (index == ID("rndr"))
            return 40;
         else
            return (int)this;
      }

      const char*
      getCode()
      {
         return "sk";
      }

      Entity*
      getClone()
      {
         return new Spike();
      }

      void render(WINDOW*, Camera*);

      Rect getBoundingBox();
      void handleCollision(Entity*);

      std::string getDescription();
};

#endif // SPIKE_H_INCLUDED
