#ifndef NULLSTATE_H_INCLUDED
#define NULLSTATE_H_INCLUDED

#include "../Application/State.h"

class NullState : public State
{
   public:
      NullState(Application* host) : State(host) {}

      void update() {}
      void render() {}
};

#endif // NULLSTATE_H_INCLUDED
