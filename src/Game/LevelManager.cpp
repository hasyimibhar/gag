#include <fstream>

#include "LevelManager.h"
#include "../Application/Application.h"
#include "../Common/Log.h"
#include "../Common/Common.h"

#include "../Entities/Tile.h"
#include "../Entities/PlayerSpawnPoint.h"
#include "../Entities/PlayerCheckPoint.h"
#include "../Entities/Mushroom.h"
#include "../Entities/Goal.h"
#include "../Entities/Spike.h"
#include "../Entities/InfoPopup.h"

LevelManager::LevelManager()
{
   mappings_["tl"] = new Tile(0, COLOR_WHITE, COLOR_BLACK, 0, -1, -1);
   mappings_["sp"] = new PlayerSpawnPoint();
   mappings_["cp"] = new PlayerCheckPoint();
   mappings_["ms"] = new Mushroom(Mushroom::DIR_LEFT);
   mappings_["gl"] = new Goal();
   mappings_["sk"] = new Spike();
   mappings_["ip"] = new InfoPopup("Hello world! You just wasted 3 seconds of your life reading this.");
}

LevelManager::~LevelManager()
{
   for (std::map<std::string, Entity*>::iterator i = mappings_.begin(); i != mappings_.end(); i++)
      delete (*i).second;
}

void
LevelManager::save(std::string fileName,
                   World*      world)
{
   std::ofstream level;
   level.open(fileName.c_str(), std::ios::binary);

   if (!level.is_open())
   {
      Log::getInstance().write("Could not find level: %s", fileName.c_str());
      Application::getInstance().finish(1);
      return;
   }

   std::vector<Entity*>& entities = world->getIndex(ID("entt"));

   int nEntities = 0;
   FOREACH(vector, Entity*, e, entities)
   {
      (*e)->save(level);
      nEntities++;
   }

   /*
   level.put('b');
   level.put('t');

   Log::getInstance().write("Successfully saved %d entities.", nEntities);
   long long packed = Pack754_64(world->getBestTime());

   level.write(world->getBestUser().c_str(), 16);
   level << packed;
   */

   //unsigned char buffer[8];
   //PackInteger64(buffer, packed);

   //for (int i = 0; i < 8; i++)
   //   level.put(buffer[i]);

   //Log::getInstance().write("Saved best user: %s", world->getBestUser().c_str());
   //Log::getInstance().write("Saved best time: %.2f", world->getBestTime());

   level.close();
   level.clear();
}

void
LevelManager::load(std::string fileName,
                   World*      world)
{
   std::ifstream level;
   level.open(fileName.c_str(), std::ios::binary);

   if (!level.is_open())
   {
      Log::getInstance().write("Could not find level: %s", fileName.c_str());
      Application::getInstance().finish(1);
      return;
   }

   char codeBuffer[3] = "  ";

   int nEntities = 0;
   while (!level.eof())
   {
      codeBuffer[0] = level.get();
      codeBuffer[1] = level.get();

      if (codeBuffer[0] == -1 || codeBuffer[1] == -1)
         break;

      Entity* entity = mappings_[codeBuffer];

      if (entity == 0)
      {
         Log::getInstance().write("Invalid entity mapping for code %s.", codeBuffer);
         Application::getInstance().finish(1);
         return;
      }

      entity = entity->getClone();
      entity->load(level);
      world->add(entity);
      nEntities++;
   }

   /*
   unsigned char buffer[8];
   for (int i = 0; i < 8; i++)
   {
      buffer[i] = level.get();
   }
   */

   /*
   long long packed;
   char buffer[17];
   level.read(buffer, 16);
   level >> packed;
   world->setBestUser(buffer);
   world->setBestTime(Unpack754_64(packed));
   */

   Log::getInstance().write("Successfully loaded %d entities.", nEntities);
   //Log::getInstance().write("Level best user is %s.", world->getBestUser().c_str());
   //Log::getInstance().write("Level best time is %.2f.", world->getBestTime());

   level.close();
   level.clear();
}
