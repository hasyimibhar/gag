#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

enum StateID
{
   STATE_NULL,
   STATE_MAINMENU,
   STATE_HIGHSCORE,
   STATE_GAME,
   STATE_EDITOR,
   STATE_CREDITS
};

class Application;

class State
{
   public:
      State(Application* host) : host_(host) {}

      virtual void update() = 0;
      virtual void render() = 0;
      virtual ~State() {}

   protected:
      Application* host_;
};

#endif // STATE_H_INCLUDED
