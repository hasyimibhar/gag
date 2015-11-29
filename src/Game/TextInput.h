#ifndef TEXTINPUT_H_INCLUDED
#define TEXTINPUT_H_INCLUDED

#include <string>

#include "../Common/Singleton.h"
#include "../Common/Timer.h"

class TextInput : public Singleton<TextInput>
{
   public:
      static const int MAX_IDLE_TIME   = 500;

      void update(int);
      void render(WINDOW*);

      std::string getText()
      {
         return text_;
      }

      void clearText()
      {
         text_.clear();
      }

   private:
      std::string text_;
      Timer       idleTimer_;
};

#endif // TEXTINPUT_H_INCLUDED
