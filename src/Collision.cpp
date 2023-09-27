#include "Collision.h"

Collision::Collision()
{

}

Collision::~Collision()
{

}

Collision::Type
Collision::gameobjectCheck(GameObject& affector, GameObject& affected)
{
  // this function goes through every possible combination and outcome when two sprites collide
  // first we update and get the latest position of our two sprites touching each other
  affector.updateBoundingBox();  // affector is the sprite colliding with the affected sprite
  affected.updateBoundingBox();  // affected is the sprite being collided with the affector sprite
  // affector bottom right intersecting affected top left
  if (affector.top_r_x > affected.top_l_x
      && affector.top_r_x < affected.top_r_x
      && affector.bot_l_y > affected.top_l_y
      && affector.bot_l_y < affected.bot_l_y)
  {
    // if there is any collision, we do one more comparison to see if the colliding sprite is on the top side or left side of the collided sprite
    // this is done by measuring the x difference and y difference, and seeing which one is bigger or smaller. google AABB collision for nice diagrams
    if ((affector.bot_l_y - affected.top_l_y) < (affector.top_r_x - affected.top_l_x))
      return Type::TOP;
    else
      return Type::LEFT;
  }
  // affector bottom left intersecting affected top right
  if (affector.top_l_x > affected.top_l_x
      && affector.top_l_x < affected.top_r_x
      && affector.bot_l_y > affected.top_l_y
      && affector.bot_l_y < affected.bot_l_y)
  {
    if ((affector.bot_l_y - affected.top_l_y) < (affected.top_r_x - affector.top_l_x))
      return Type::TOP;
    else
      return Type::RIGHT;
  }
  // affector top right intersecting affected bottom left
  if (affector.top_r_x > affected.top_l_x
      && affector.top_r_x < affected.top_r_x
      && affector.top_l_y > affected.top_l_y
      && affector.top_l_y < affected.bot_l_y)
  {
    if ((affected.bot_l_y - affector.top_l_y) < (affector.top_r_x - affected.top_l_x))
      return Type::BOTTOM;
    else
      return Type::LEFT;
  }
  // affector top left intersection affected bottom right
  if (affector.top_l_x > affected.top_l_x
      && affector.top_l_x < affected.top_r_x
      && affector.top_l_y > affected.top_l_y
      && affector.top_l_y < affected.bot_l_y)
  {
    if ((affected.bot_l_y - affector.top_l_y) < (affected.top_r_x - affector.top_l_x))
      return Type::BOTTOM;
    else
      return Type::RIGHT;
  }
  else
  {
    return Type::NONE;
    // if there is absolutely no collisions, it returns NONE
  }
}

Collision::Type
Collision::windowCheck(GameObject& affector, sf::RenderWindow& window)
{
  // this just checks if sprites are hitting the window or not. uses same enum Type for same reason as before
  affector.updateBoundingBox();
  if (affector.top_r_x > window.getSize().x)
    return Type::RIGHT;

  if (affector.top_l_x < 0)
    return Type::LEFT;

  if (affector.bot_l_y > window.getSize().y)
    return Type::BOTTOM;

  if (affector.top_l_y < 0)
    return Type::TOP;

  else
    return Type::NONE;
}