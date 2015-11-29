#ifndef INFOPOPUP_H_INCLUDED
#define INFOPOPUP_H_INCLUDED

#include <string>

#include "../Game/Entity.h"
#include "../Common/Log.h"

class InfoPopup : public Entity
{
   public:
      static const int MAX_TEXT_LENGTH    =  512;

      InfoPopup(std::string);

      int*
      getIndices()
      {
         static int indices[] = { ID("entt"), ID("coll"), ID("inpo"), 0 };
         return indices;
      }

      const char*
      getCode()
      {
         return "ip";
      }

      int
      getOrder(int index)
      {
         if (index == ID("rndr"))
            return 20;
         else
            return (int)this;
      }

      Entity*
      getClone()
      {
         return new InfoPopup(text_);
      }

      void render(WINDOW*, Camera*);

      Rect getBoundingBox();
      std::string getDescription();

      void handleCollision(Entity*);

      void
      setText(std::string text)
      {
         strcpy(text_, text.c_str());
         Log::getInstance().write("The text is: %s.", text_);
      }

      void save(std::ofstream&);
      void load(std::ifstream&);

   private:
      bool        isTouched_;
      char        text_[MAX_TEXT_LENGTH + 1];
};

#endif // INFOPOPUP_H_INCLUDED
