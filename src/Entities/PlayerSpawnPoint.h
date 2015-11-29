#ifndef PLAYERSPAWNPOINT_H_INCLUDED
#define PLAYERSPAWNPOINT_H_INCLUDED

#include "../Game/Entity.h"

class PlayerSpawnPoint : public Entity
{
   public :
      int*
      getIndices()
      {
         static int indices[] = { ID("entt"), ID("rndr"), ID("spwn"), 0 };
         return indices;
      }

      const char*
      getCode()
      {
         return "sp";
      }

      Entity*
      getClone()
      {
         return new PlayerSpawnPoint();
      }

      void render(WINDOW*, Camera*);

      Rect getBoundingBox();
      std::string getDescription();
};

#endif // PLAYERSPAWNPOINT_H_INCLUDED
