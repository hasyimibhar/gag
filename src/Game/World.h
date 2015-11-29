#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include <map>

#include "Entity.h"

class EntityCompare
{
   public:
      EntityCompare(int id) : id(id) {}

      bool operator() (Entity *a, Entity *b)
      {
         return a->getOrder(id) < b->getOrder(id);
      }

   private:
      int id;
};

class World
{
   public:
      World();

      void add(Entity*);
      void remove(Entity*);
      void reindex();

      std::vector<Entity*>&
      getIndex(int id)
      {
         return indices_[id];
      };

      Entity*
      getEntity(int id)
      {
         return (getIndex(id).size()) ? getIndex(id).front() : NULL;
      }

   private:
      std::map<int, std::vector<Entity*> > indices_;
      std::vector<Entity*> toAdd_, toRemove_;
};

#endif // WORLD_H_INCLUDED
