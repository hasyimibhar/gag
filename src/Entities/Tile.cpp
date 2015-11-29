#include "Tile.h"
#include "../Common/ColorPairManager.h"
#include "../Common/Log.h"
#include "../Common/Common.h"
#include "../Game/GameContent.h"

Tile::Tile(int       texture,
           int       foreground,
           int       background,
           Level*    level,
           int       x,
           int       y) : texture_(texture), foreground_(foreground), background_(background),
                          level_(level)
{
   setX(x);
   setY(y);
}

void
Tile::render(WINDOW* window,
             Camera* camera)
{
   wattron(window,
           COLOR_PAIR(ColorPairManager::getInstance().getColorPair(foreground_, background_)));

   mvwaddch(window, (int)position_.y - camera->getY(), (int)position_.x - camera->getX(), texture_);

   wattroff(window,
           COLOR_PAIR(ColorPairManager::getInstance().getColorPair(foreground_, background_)));
}

void
Tile::save(std::ofstream& file)
{
   Entity::save(file);

   unsigned char textureBuffer[4];
   PackInteger32(textureBuffer, texture_);

   for (int i = 0; i < 4; i++)
      saveByte(file, textureBuffer[i]);

   saveByte(file, foreground_);
   saveByte(file, background_);
}

void
Tile::load(std::ifstream& file)
{
   Entity::load(file);

   unsigned char textureBuffer[4];
   for (int i = 0; i < 4; i++)
      textureBuffer[i] = loadByte(file);

   texture_    = UnpackInteger32(textureBuffer);
   foreground_ = loadByte(file);
   background_ = loadByte(file);
}

Rect
Tile::getBoundingBox()
{
   return Rect(position_.x, position_.y, position_.x, position_.y);
}

std::string
Tile::getDescription()
{
   return "A tile, which is the building block of a level. Comes in various colors.";
}
