#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "../Game/Entity.h"

class Level;

class Tile : public Entity
{
   public:
      Tile(int, int, int, Level*, int, int);

      int*
      getIndices()
      {
         static int indices[] = { ID("entt"), ID("rndr"), ID("tile"), 0 };
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

      const char*
      getCode()
      {
         return "tl";
      }

      Entity*
      getClone()
      {
         return new Tile(texture_, foreground_, background_, level_, (int)position_.x, (int)position_.y);
      }

      void
      setLevel(Level* level, int x, int y)
      {
         level_ = level;
         setX(x);
         setY(y);
      }

      void render(WINDOW*, Camera*);

      void save(std::ofstream&);
      void load(std::ifstream&);

      Rect getBoundingBox();

      std::string getDescription();

   private:
      int  texture_;
      int  foreground_, background_;
      Level* level_;
};

#endif // TILE_H_INCLUDED
