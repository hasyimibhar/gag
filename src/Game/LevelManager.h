#ifndef LEVELMANAGER_H_INCLUDED
#define LEVELMANAGER_H_INCLUDED

#include <map>
#include <string>

#include "../Common/Singleton.h"
#include "Entity.h"
#include "World.h"

class LevelManager : public Singleton<LevelManager>
{
   public:
      LevelManager();
      ~LevelManager();

      void save(std::string, World*);
      void load(std::string, World*);

   private:
      std::map<std::string, Entity*> mappings_;
};

#endif // LEVELMANAGER_H_INCLUDED
