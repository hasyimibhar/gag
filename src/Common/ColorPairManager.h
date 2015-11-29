#ifndef COLORPAIRMANAGER_H_INCLUDED
#define COLORPAIRMANAGER_H_INCLUDED

#include "Singleton.h"

class ColorPairManager : public Singleton<ColorPairManager>
{
   public:
      static const int MAX_COLOR_PAIRS = 64;
      static const int MAX_COLORS      = 8;

      ColorPairManager();

      int getColorPair(int, int);

   private:
      int colorPairs_[MAX_COLOR_PAIRS][2];
};

#endif // COLORPAIRMANAGER_H_INCLUDED
