#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <curses.h>

#include "../Entities/Tile.h"
#include "World.h"

class Level
{
   public:
      static const int LEVEL_WIDTH   =  3000;
      static const int LEVEL_HEIGHT  =  100;

      Level();
      ~Level();

      void  addTiles(World*);
      Tile* getTile(int, int);

      void  setup();

   private:
      Tile* tiles_[LEVEL_HEIGHT][LEVEL_WIDTH];
      double bestTime_;
};

#endif // LEVEL_H_INCLUDED
