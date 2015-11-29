#ifndef EDITORSTATE_H_INCLUDED
#define EDITORSTATE_H_INCLUDED

#include <vector>
#include <string>

#include "../Application/State.h"
#include "../Game/Entity.h"
#include "../Game/Level.h"
#include "../Game/World.h"
#include "../Game/Camera.h"

class EditorState : public State
{
   public:
      EditorState(Application*);
      ~EditorState();

      void update();
      void render();

   private:
      World                      world;
      Camera*                    dummy;
      std::vector<Entity*>       pallete_;
      Entity*                    clipboard_;
      Entity*                    entities_[Level::LEVEL_HEIGHT][Level::LEVEL_WIDTH];
      int                        pX_, pY_;
      int                        selected_;
      std::string                currentFileName_;
      bool                       isAutoPutOn_;
      bool                       isPanningModeOn_;
      bool                       isModified_;
};

#endif // EDITORSTATE_H_INCLUDED
