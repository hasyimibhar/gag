#include <cassert>
#include <curses.h>

#include "ColorPairManager.h"
#include "Log.h"

ColorPairManager::ColorPairManager()
{
   for (int i = 0; i < MAX_COLOR_PAIRS; i++)
      for (int j = 0; j < 2; j++)
         colorPairs_[i][j] = -1;
}

int
ColorPairManager::getColorPair(int foreground,
                               int background)
{
   assert(foreground >= 0 && foreground < MAX_COLORS && "Invalid foreground color!");
   assert(background >= 0 && background < MAX_COLORS && "Invalid background color!");

   int iColorPair;
   for (iColorPair = 0; iColorPair < MAX_COLOR_PAIRS; iColorPair++)
   {
      if (colorPairs_[iColorPair][0] == -1)
         break;

      if (foreground == colorPairs_[iColorPair][0] &&
          background == colorPairs_[iColorPair][1])
         return iColorPair + 1;
   }

   init_pair(iColorPair + 1, foreground, background);
   colorPairs_[iColorPair][0] = foreground;
   colorPairs_[iColorPair][1] = background;
   Log::getInstance().write("Created a color pair with ID %d: %d, %d", iColorPair + 1, foreground, background);
   return iColorPair + 1;
}
