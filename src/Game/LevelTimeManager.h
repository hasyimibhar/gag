#ifndef LEVELTIMEMANAGER_H_INCLUDED
#define LEVELTIMEMANAGER_H_INCLUDED

#include <string>
#include <map>

#include "../Common/Singleton.h"

struct LevelTime
{
   std::string user;
   double      time;
};

class LevelTimeManager : public Singleton<LevelTimeManager>
{
   public:
      void       addLevelTime(std::string, std::string, double);
      LevelTime* getLevelTime(std::string);

      void      save();
      void      load();

   private:
      std::map<std::string, LevelTime*> records_;
};

#endif // LEVELTIMEMANAGER_H_INCLUDED
