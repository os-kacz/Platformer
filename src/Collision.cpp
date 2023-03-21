#include "Collision.h"

Collision::Collision()
{

}

Collision::~Collision()
{

}

bool Collision::gameobjectCheck(GameObject& affector, GameObject& affected)
{
  affector.getBoundingBox();
  affected.getBoundingBox();
  if (affector.top_r_x > affected.top_l_x
      && affector.top_r_x < affected.top_r_x
      && affector.bot_l_y > affected.top_l_y
      && affector.bot_l_y < affected.bot_l_y)
  {
    return true;
  }
  if (affector.top_l_x > affected.top_l_x
      && affector.top_l_x < affected.top_r_x
      && affector.bot_l_y > affected.top_l_y
      && affector.bot_l_y < affected.bot_l_y)
  {
    return true;
  }
  if (affector.top_r_x > affected.top_l_x
      && affector.top_r_x < affected.top_r_x
      && affector.top_l_y > affected.top_l_y
      && affector.top_l_y < affected.bot_l_y)
  {
    return true;
  }
  if (affector.top_l_x > affected.top_l_x
      && affector.top_l_x < affected.top_r_x
      && affector.top_l_y > affected.top_l_y
      && affector.top_l_y < affected.bot_l_y)
  {
    return true;
  }
  else
  {
    return false;
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