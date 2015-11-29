#include <fstream>
using namespace std;

#include "LevelTimeManager.h"
#include "../Common/Log.h"
#include "../Common/Common.h"
#include "../Application/Application.h"

void
LevelTimeManager::addLevelTime(std::string level,
                               std::string user,
                               double      time)
{
   if (records_[level] != 0)
   {
      double currentTime = records_[level]->time;
      if (time < currentTime)
      {
         records_[level]->user = user;
         records_[level]->time = time;
      }
   }
   else
   {
      records_[level] = new LevelTime();
      records_[level]->user = user;
      records_[level]->time = time;
   }

   save();
}

LevelTime*
LevelTimeManager::getLevelTime(std::string level)
{
   return records_[level];
}

void
LevelTimeManager::save()
{
   ofstream times;
   times.open("times.dat", ios::binary);

   if (!times.is_open())
   {
      Log::getInstance().write("Failed to open \"times.dat\"!");
      Application::getInstance().finish(1);
   }
   else
   {
      for (std::map<std::string, LevelTime*>::iterator i = records_.begin(); i != records_.end(); i++)
      {
         times.write((*i).first.c_str(), 25);
         times.write((*i).second->user.c_str(), 16);
         times << Pack754_64((*i).second->time);
      }

      times.close();
      times.clear();
   }
}

void
LevelTimeManager::load()
{
   ifstream times;
   times.open("times.dat", ios::binary);

   if (!times.is_open())
   {
      ofstream times;
      times.open("times.dat", ios::binary);
      times.close();
      times.clear();
   }
   else
   {
      while (!times.eof())
      {
         char levelBuffer[26];
         times.read(levelBuffer, 25);
         string level = levelBuffer;

         char userBuffer[17];
         times.read(userBuffer, 16);
         string user = userBuffer;

         long long packed;
         times >> packed;

         records_[level] = new LevelTime();
         records_[level]->user = user;
         records_[level]->time = Unpack754_64(packed);
      }

      times.close();
      times.clear();
   }
}
