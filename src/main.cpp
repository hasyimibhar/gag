#include "Common/Log.h"
#include "Application/Application.h"

int
main(int   argc,
     char* agrv[])
{
   new Log();
   Log::getInstance().initialize();
   Log::getInstance().write("Logging utility initialized.");

   new Application();
   if (!Application::getInstance().start())
   {
      Log::getInstance().write("Failed to start application.");
      delete Application::getInstancePointer();
      return 1;
   }

   Application::getInstance().run();
   Application::getInstance().stop();

   delete Application::getInstancePointer();
   delete Log::getInstancePointer();

   return 0;
}
