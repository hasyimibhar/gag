#ifndef MUSHROOM_H_INCLUDED
#define MUSHROOM_H_INCLUDED

#include "../Game/Entity.h"

class Mushroom : public Entity
{
   public:
      static const double WALK_SPEED = 0.2f;

      enum Direction
      {
         DIR_LEFT,
         DIR_RIGHT
      };

      Mushroom(Direction);

      int*
      getIndices()
      {
         static int indices[] = { ID("entt"), ID("rndr"), ID("updt"), ID("mush"), ID("coll"), ID("pcol"),0 };
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
         return "ms";
      }

      Entity*
      getClone()
      {
         return new Mushroom(direction_);
      }

      void
      setDirection(Direction direction)
      {
         direction_ = direction;
      }

      Direction
      getDirection()
      {
         return direction_;
      }

      void update();
      void render(WINDOW*, Camera*);

      Rect getBoundingBox();
      void handleCollision(Entity*);

      std::string getDescription();

   private:
      Vec       velocity_;
      Direction direction_;
};

#endif // MUSHROOM_H_INCLUDED
