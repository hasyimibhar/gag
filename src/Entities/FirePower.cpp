#include <vector>

#include "../Game/GameContent.h"
#include "FirePower.h"
#include "../Common/Log.h"
#include "../Common/Common.h"
#include "../Common/ColorPairManager.h"

FirePower::FirePower()
{
   flash();
   //Log::getInstance().write("Now burn everything!");
   position_ = Vec(0.0, LINES - 1);
}

void
FirePower::update()
{
   position_.y -= 1.0f;

   if (position_.y < 0)
   {
      flash();

      std::vector<Entity*> entities =
         GameContent::getInstance().getCamera()->getEntitiesInView(GameContent::getInstance().getWorld(), ID("pcol"));

      FOREACH(vector, Entity*, e, entities)
         (*e)->discard();

      discard();
   }
}

void
FirePower::render(WINDOW* window,
                  Camera* camera)
{
   wattron(window, COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_RED, COLOR_BLACK)) | A_BOLD);

   for (int j = 0; j < 5; j++)
      for (int i = 0; i < COLS; i++)
         mvwaddch(window, (int)position_.y - j, i, '^');

   wattroff(window, COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_RED, COLOR_BLACK)) | A_BOLD);
}
