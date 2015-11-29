#ifndef GOAL_H_INCLUDED
#define GOAL_H_INCLUDED

#include "../Game/Entity.h"

class Goal : public Entity
{
   public:
      int*
      getIndices()
      {
         static int indices[] = { ID("entt"), ID("rndr"), ID("goal"), ID("coll"), 0 };
         return indices;
      }

      const char*
      getCode()
      {
         return "gl";
      }

      Entity*
      getClone()
      {
         return new Goal();
      }

      void render(WINDOW*, Camera*);

      Rect getBoundingBox();

      std::string getDescription();
};

#endif // GOAL_H_INCLUDED
