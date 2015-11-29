#ifndef GAMECONTENT_H_INCLUDED
#define GAMECONTENT_H_INCLUDED

#include <stack>

#include "../Common/Singleton.h"
#include "../Common/Timer.h"
#include "World.h"
#include "Level.h"
#include "../Entities/Player.h"
#include "../Entities/PlayerSpawnPoint.h"
#include "Camera.h"

class GameContent : public Singleton<GameContent>
{
   public:
      GameContent();
      ~GameContent();

      World* getWorld();

      Level* getLevel();
      void setLevel(Level*);

      Player* getPlayer();
      void setPlayer(Player*);

      Camera* getCamera();
      void setCamera(Camera*);

      int getPlayerLives();
      void setPlayerLives(int nPlayerLives);
      void decrementPlayerLives();

      bool setupGame(std::string);

      Vec getPlayerSpawnPoint();
      void setPlayerSpawnPoint(Vec);

      std::string getCurrentLevel();
      void addLevel(std::string);
      void popLevel();

      bool isTestMode();
      void setTestMode(bool);

      bool isLevelOver();
      void setLevelOver(bool);

      void     startGameTime();
      void     stopGameTime();
      double   getElapsedGameTime();

   private:
      World* world_;
      Level* level_;
      Player* player_;
      Vec     playerSpawnPoint_;
      Camera* camera_;

      std::stack<std::string> levelFiles_;

      int nPlayerLives_;
      bool isTestMode_;

      bool isLevelOver_;

      Timer timer_;
};

#endif // GAMECONTENT_H_INCLUDED
