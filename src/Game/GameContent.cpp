#include "GameContent.h"
#include "LevelManager.h"
#include "../Common/Log.h"
#include "../Common/Common.h"

GameContent::GameContent()
{
   world_ = new World();
   level_ = new Level();
   camera_ = new Camera(0, 0);
   player_ = 0;
}

GameContent::~GameContent()
{
   delete camera_;
   delete world_;
   delete level_;
}

World*
GameContent::getWorld()
{
   return world_;
}

Level*
GameContent::getLevel()
{
   return level_;
}

void
GameContent::setLevel(Level* level)
{
   if (level_ != 0) delete level_;
   level_ = level;
}

Player*
GameContent::getPlayer()
{
   if (player_ != 0)
      return player_;

   return 0;
}

void
GameContent::setPlayer(Player* player)
{
   player_ = player;
}

Camera*
GameContent::getCamera()
{
   return camera_;
}

void
GameContent::setCamera(Camera* camera)
{
   camera_ = camera;
}

int
GameContent::getPlayerLives()
{
   return nPlayerLives_;
}

void
GameContent::setPlayerLives(int nPlayerLives)
{
   nPlayerLives_ = nPlayerLives;
}

void
GameContent::decrementPlayerLives()
{
   if (!isTestMode_ && nPlayerLives_ > 0)
      nPlayerLives_--;
}

Vec
GameContent::getPlayerSpawnPoint()
{
   return playerSpawnPoint_;
}

void
GameContent::setPlayerSpawnPoint(Vec playerSpawnPoint)
{
   playerSpawnPoint_ = playerSpawnPoint;
}

bool
GameContent::setupGame(std::string levelName)
{
   isLevelOver_ = false;

   delete camera_;
   delete world_;
   delete level_;
   delete player_;

   world_ = new World();
   level_ = new Level();
   camera_ = new Camera(0, 0);

   LevelManager::getInstance().load(levelName, world_);
   world_->reindex();

   PlayerSpawnPoint* playerSpawnPoint = static_cast<PlayerSpawnPoint*>(world_->getEntity(ID("spwn")));

   if (playerSpawnPoint == 0)
   {
      Log::getInstance().write("Map does not contain player spawn point!");
      return false;
   }

   playerSpawnPoint_ = playerSpawnPoint->getPosition();

   FOREACH(vector, Entity*, e, world_->getIndex(ID("spwn")))
   {
      (*e)->discard();
   }

   world_->reindex();

   Level* level = new Level();
   level->addTiles(world_);
   level_ = level;

   return true;
}

std::string
GameContent::getCurrentLevel()
{
   if (levelFiles_.size() > 0)
      return levelFiles_.top();

   return "";
}

void
GameContent::addLevel(std::string level)
{
   levelFiles_.push(level);
}

void
GameContent::popLevel()
{
   if (levelFiles_.size() > 0)
      levelFiles_.pop();
}

bool
GameContent::isTestMode()
{
   return isTestMode_;
}

void
GameContent::setTestMode(bool isTestMode)
{
   isTestMode_ = isTestMode;
}

bool
GameContent::isLevelOver()
{
   return isLevelOver_;
}

void
GameContent::setLevelOver(bool isLevelOver)
{
   isLevelOver_ = isLevelOver;
}

void
GameContent::startGameTime()
{
   timer_.start();
}

void
GameContent::stopGameTime()
{
   timer_.reset();
}

double
GameContent::getElapsedGameTime()
{
   return timer_.getElapsedTime();
}
