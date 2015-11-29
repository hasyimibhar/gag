#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <fstream>

#include "Singleton.h"

class Log : public Singleton<Log>
{
   public:
      void initialize();
      void write(const char*, ...);

   private:
      std::ofstream fileStream_;
};

#endif // LOG_H_INCLUDED
