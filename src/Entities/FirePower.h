#ifndef FIREPOWER_H_INCLUDED
#define FIREPOWER_H_INCLUDED

#include "../Game/Entity.h"

class FirePower : public Entity
{
   public:
      FirePower();

      int*
      getIndices()
      {
         static int indices[] = { ID("entt"), ID("rndr"), ID("updt"), ID("powr"), 0 };
         return indices;
      }

      int
      getOrder(int index)
      {
         if (index == ID("rndr"))
            return 50;
         else
            return (uintptr_t)this;
      }

      void update();
      void render(WINDOW*, Camera*);
};

#endif // FIREPOWER_H_INCLUDED
