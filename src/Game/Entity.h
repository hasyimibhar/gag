#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <fstream>
#include <curses.h>

#include "../Common/Vector2D.h"

#define ID(str) (((str[3] * 256 + str[2]) * 256 + str[1]) * 256 + str[0])

class World;
class Camera;

class Entity
{
   public:
      virtual ~Entity() {}

      void
      setWorld(World* world)
      {
         world_ = world;
      }

      World*
      getWorld()
      {
         return world_;
      }

      virtual int*
      getIndices()
      {
         static int indices[1] = { 0 };
         return indices;
      }

      virtual void discard();

      virtual int
      getOrder(int index)
      {
         return (uintptr_t)this;
      }

      virtual Vec
      getPosition()
      {
         return position_;
      }

      virtual double
      getX()
      {
         return position_.x;
      }

      virtual double
      getY()
      {
         return position_.y;
      }

      virtual void
      setPosition(Vec position)
      {
         position_ = position;
      }

      virtual void
      setX(double x)
      {
         position_.x = x;
      }

      virtual void
      setY(double y)
      {
         position_.y = y;
      }

      virtual void update() {}
      virtual void render(WINDOW* window, Camera* camera) {}

      virtual Rect
      getBoundingBox()
      {
         return Rect(0, 0, 0, 0);
      }

      virtual std::string
      getDescription()
      {
         return "Undefined.";
      }

      virtual void save(std::ofstream&);
      virtual void load(std::ifstream&);

      virtual Entity*
      getClone()
      {
         return NULL;
      }

      virtual void handleCollision(Entity* entity) {}

   protected:
      World* world_;
      Vec    position_;

      void saveByte(std::ofstream&, char);
      int  loadByte(std::ifstream&);

      virtual const char*
      getCode()
      {
         return "XX";
      }
};

#endif // ENTITY_H_INCLUDED
