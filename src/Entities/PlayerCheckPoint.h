#ifndef PLAYERCHECKPOINT_H_INCLUDED
#define PLAYERCHECKPOINT_H_INCLUDED

#include "../Game/Entity.h"

class PlayerCheckPoint : public Entity
{
   public:
      PlayerCheckPoint();

      int*
      getIndices()
      {
         static int indices[] = { ID("entt"), ID("rndr"), ID("coll"), ID("chek"), 0 };
         return indices;
      }

      const char*
      getCode()
      {
         return "cp";
      }

      int
      getOrder(int index)
      {
         if (index == ID("rndr"))
            return 20;
         else
            return (uintptr_t)this;
      }

      Entity*
      getClone()
      {
         return new PlayerCheckPoint();
      }

      void render(WINDOW*, Camera*);

      Rect getBoundingBox();
      std::string getDescription();

      void handleCollision(Entity*);

   private:
      bool isTouched_;
};

#endif // PLAYERCHECKPOINT_H_INCLUDED
