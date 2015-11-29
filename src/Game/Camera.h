#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "World.h"

class Camera
{
   public:
      Camera(int, int);

      std::vector<Entity*> getEntitiesInView(World*, int);

      int getX() { return x_; }
      int getY() { return y_; }

      void setPosition(int x,
                       int y)
      {
         x_ = x;
         y_ = y;
      }

      void followEntity(Entity* entity,
                        int     xOffset,
                        int     yOffset)
      {
         setPosition((int)entity->getX() + xOffset, (int)entity->getY() + yOffset);
      }

      void clamp(int, int, int, int);

   private:
      int x_, y_;
};

#endif // CAMERA_H_INCLUDED
