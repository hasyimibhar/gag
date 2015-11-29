#include "Camera.h"
#include "../Common/Vector2D.h"
#include "../Common/Common.h"
#include "../Common/Log.h"

Camera::Camera(int x,
               int y) : x_(x), y_(y)
{
}

std::vector<Entity*>
Camera::getEntitiesInView(World* world,
                          int    indexID)
{
   std::vector<Entity*> entities = world->getIndex(indexID);
   std::vector<Entity*> toRemove;
   Rect camera = Rect(x_, y_, x_ + COLS, y_ + LINES);

   //Log::getInstance().write("Camera is at %d, %d.", x_, y_);

   FOREACH(vector, Entity*, e, entities)
   {
      if (!(*e)->getBoundingBox().collide(camera))
      {
         toRemove.push_back(*e);
      }
   }

   FOREACH(vector, Entity*, e, toRemove)
   {
      remove_element(entities, *e);
   }

   toRemove.clear();

   return entities;
}

void
Camera::clamp(int minX,
              int minY,
              int maxX,
              int maxY)
{
   if (x_ < minX)
      x_ = minX;

   else if (x_ + COLS > maxX)
      x_ = maxX - COLS;

   if (y_ < minY)
      y_ = minY;

   else if (y_ + LINES > maxY)
      y_ = maxY - LINES;
}
