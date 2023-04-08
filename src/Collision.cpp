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
  affector.getBoundingBox();
  affected.getBoundingBox();
  // affector bottom right intersecting affected top left
  if (affector.top_r_x > affected.top_l_x
      && affector.top_r_x < affected.top_r_x
      && affector.bot_l_y > affected.top_l_y
      && affector.bot_l_y < affected.bot_l_y)
  {
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
  }
}

Collision::Type
Collision::windowCheck(GameObject& affector, sf::RenderWindow& window)
{
  affector.getBoundingBox();
  if (affector.top_r_x > window.getSize().x)
  {
    return Type::RIGHT;
  }

  if (affector.top_l_x < 0)
  {
    return Type::LEFT;
  }

  if (affector.bot_l_y > window.getSize().y)
  {
    return Type::BOTTOM;
  }

  if (affector.top_l_y < 0)
  {
    return Type::TOP;
  }
  else
  {
    return Type::NONE;
  }
}