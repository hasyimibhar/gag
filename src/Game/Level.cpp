#include <vector>
#include <cassert>

#include "Level.h"
#include "../Common/Common.h"

Level::Level()
{
   for (int i = 0; i < LEVEL_HEIGHT; i++)
      for (int j = 0; j < LEVEL_WIDTH; j++)
         tiles_[i][j] = 0;

   bestTime_ = 0.0;
}

Level::~Level()
{
   for (int i = 0; i < LEVEL_HEIGHT; i++)
      for (int j = 0; j < LEVEL_WIDTH; j++)
         delete tiles_[i][j];
}

void
Level::addTiles(World* world)
{
   std::vector<Entity*>& tiles = world->getIndex(ID("tile"));

   FOREACH(vector, Entity*, e, tiles)
   {
      tiles_[(int)(*e)->getY()][(int)(*e)->getX()] = static_cast<Tile*>(*e);
   }

   setup();
}

Tile*
Level::getTile(int x,
               int y)
{
   //assert(x < LEVEL_WIDTH && "Tile x-coordinate out of bounds.");
   //assert(y < LEVEL_HEIGHT && "Tile y-coordinate out of bounds.");

   if (x < LEVEL_WIDTH && y < LEVEL_HEIGHT)
      return tiles_[y][x];

   return 0;
}

void
Level::setup()
{
   for (int i = 0; i < LEVEL_HEIGHT; i++)
      for (int j = 0; j < LEVEL_WIDTH; j++)
         if (tiles_[i][j] != 0)
            tiles_[i][j]->setLevel(this, j, i);
}
