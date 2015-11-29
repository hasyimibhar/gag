#include <curses.h>

#include "Player.h"
#include "../Game/CollisionManager.h"
#include "../Game/GameContent.h"
#include "../Common/Log.h"
#include "../Common/Common.h"
#include "../Application/Application.h"

#include "Goal.h"

Player::Player()
{
   position_ = Vec(2, 2);
   velocity_ = Vec(0.0f, 0.0f);
   state_    = STATE_FALLING;
   isAlive_  = true;
}

Player::~Player()
{
}

Rect
Player::getBoundingBox()
{
   return Rect(position_.x - 0.5f, position_.y - 0.5f, position_.x + 0.5f, position_.y + 0.5f);
}

void
Player::handleCollisions()
{
   Collision collision = CollisionManager::getInstance().getCollision(this, GameContent::getInstance().getLevel());

   int nRetries = 0;

   while (collision.direction != Collision::DIR_NONE && nRetries++ < 20)
   {
      switch (collision.direction)
      {
         case Collision::DIR_RIGHT :
            CollisionManager::getInstance().ejectEntity(this, collision);

            velocity_.x = 0.0f;
            state_ = STATE_FALLING;
         break;

         case Collision::DIR_UP :
            CollisionManager::getInstance().ejectEntity(this, collision);

            velocity_.y = 0.0f;
            state_ = STATE_FALLING;
         break;

         case Collision::DIR_DOWN :
            CollisionManager::getInstance().ejectEntity(this, collision);

            velocity_.y = 0.0f;

            if (!GameContent::getInstance().getLevel()->getTile((int)getBoundingBox().rightCenter().x + 1.0f, (int)getBoundingBox().rightCenter().y))
               state_ = STATE_WALKING;

            else
               state_ = STATE_STANDING;
         break;

         default :
         break;
      }

      collision = CollisionManager::getInstance().getCollision(this, GameContent::getInstance().getLevel());
   }
}

void
Player::jump()
{
   if (state_ == STATE_STANDING || state_ == STATE_WALKING)
   {
      velocity_.y = JUMP_VELOCITY;
      position_.y += velocity_.y;
      state_ = STATE_FALLING;
      Log::getInstance().write("Jump is called!");
   }
}

void
Player::update()
{
   handleCollisions();

   switch (state_)
   {
      case STATE_FALLING :
         if (!GameContent::getInstance().getLevel()->getTile((int)getBoundingBox().bottomCenter().x + 1.0f, (int)getBoundingBox().bottomCenter().y))
         {
            velocity_.x = WALK_SPEED;
         }

         if (velocity_.y < MAX_GRAVITY)
            velocity_.y += GRAVITY_ACCELERATION;

         else
            velocity_.y = MAX_GRAVITY;

         position_ += velocity_;
      break;

      case STATE_STANDING :
         if (!GameContent::getInstance().getLevel()->getTile((int)getBoundingBox().bottomCenter().x, (int)getBoundingBox().bottomCenter().y + 1.0f))
         {
            state_ = STATE_FALLING;
         }
      break;

      case STATE_WALKING :
         velocity_.x = WALK_SPEED;
         position_.x += velocity_.x;

         if (!GameContent::getInstance().getLevel()->getTile((int)getBoundingBox().bottomCenter().x, (int)getBoundingBox().bottomCenter().y + 1.0f))
         {
            state_ = STATE_FALLING;
         }
      break;

      default :
      break;
   }
}

void
Player::render(WINDOW* window,
               Camera* camera)
{
   //mvwaddstr(window, (int)position_.y - camera->getY(), (int)position_.x - camera->getX(), "oo");
   //mvwaddstr(window, (int)position_.y + 1 - camera->getY(), (int)position_.x - camera->getX(), "oo");
   mvwaddch(window, (int)position_.y - camera->getY(), (int)position_.x - camera->getX(), 399);
}

void
Player::handleCollision(Entity* entity)
{
   Goal* goal = dynamic_cast<Goal*>(entity);

   if (goal != 0 && !GameContent::getInstance().isLevelOver())
   {
      GameContent::getInstance().setLevelOver(true);
   }
}

void
Player::discard()
{
   if (isAlive_)
   {
      isAlive_ = false;
      flash();
      GameContent::getInstance().decrementPlayerLives();
      Entity::discard();
   }
}
