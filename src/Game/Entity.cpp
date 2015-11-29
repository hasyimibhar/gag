#include <fstream>

#include "Entity.h"
#include "World.h"
#include "../Common/Common.h"

void Entity::discard()
{
	world_->remove(this);
}

int Entity::loadByte(std::ifstream& file)
{
	return file.get();
}

void Entity::saveByte(std::ofstream& file, char c)
{
	file.put(c);
}

void Entity::save(std::ofstream& file)
{
	saveByte(file, getCode()[0]);
	saveByte(file, getCode()[1]);

	unsigned char posBuffer[4];

   PackInteger32(posBuffer, int(position_.x));
   for (int i = 0; i < 4; i++)
      saveByte(file, posBuffer[i]);

	PackInteger32(posBuffer, int(position_.y));
   for (int i = 0; i < 4; i++)
      saveByte(file, posBuffer[i]);
}

void Entity::load(std::ifstream& file)
{
   unsigned char posBuffer[4];

   for (int i = 0; i < 4; i++)
      posBuffer[i] = loadByte(file);
   position_.x = UnpackInteger32(posBuffer);

   for (int i = 0; i < 4; i++)
      posBuffer[i] = loadByte(file);
   position_.y = UnpackInteger32(posBuffer);

   //position_.x = loadByte(file);
   //position_.y = loadByte(file);
}
