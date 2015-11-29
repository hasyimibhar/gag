#include <cstdarg>

#include "Log.h"

void Log::initialize()
{
   fileStream_.open("log.txt");
}

void Log::write(const char* message, ...)
{
   va_list arguments;
   va_start(arguments, message);

   char buffer[1024];

   vsprintf(buffer, message, arguments);

   fileStream_ << buffer << std::endl;

#ifdef DEBUG
   fileStream_.flush();
#endif
}
