#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "../Game/Entity.h"
#include "../Common/Vector2D.h"

class Player : public Entity
{
   public:
      static const float MAX_GRAVITY               = 0.5f;
      static const float GRAVITY_ACCELERATION      = 0.00981f;
      static const float WALK_SPEED                = 0.2f;
      static const float JUMP_VELOCITY             = -0.3f;

      Player();
      ~Player();

      int*
      getIndices()
      {
         static int indices[] = { ID("entt"), ID("rndr"), ID("updt"), ID("plyr"), ID("coll"), 0 };
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
         return "pl";
      }

      Entity*
      getClone()
      {
         return new Player();
      }

      bool isAlive()
      {
         return isAlive_;
      }

      void discard();

      void update();
      void render(WINDOW*, Camera*);

      void jump();

      void handleCollisions();

      Rect getBoundingBox();

      void handleCollision(Entity*);

   private:
      enum PlayerState
      {
         STATE_STANDING,
         STATE_WALKING,
         STATE_FALLING
      };

      Vec  velocity_;
      PlayerState state_;

      bool isAlive_;
};

#endif // PLAYER_H_INCLUDED
