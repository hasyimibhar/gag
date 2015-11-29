#include <curses.h>

#include "TextInput.h"

void
TextInput::update(int key)
{
   if (key != ERR && key >= 97 && key <= 122)
   {
      text_ += key;
      idleTimer_.reset();
      idleTimer_.start();
   }

   if (idleTimer_.getElapsedTime() >= MAX_IDLE_TIME)
   {
      text_.clear();
   }
}

void
TextInput::render(WINDOW* window)
{
   int x = (COLS - text_.size()) / 2;
   for (int i = 0; i < (int)text_.size(); i++)
   {
      mvwaddstr(window, LINES - 4, x, text_.c_str());
   }
}
