#ifndef PLATFORMERSFML_COLLISION_H
#define PLATFORMERSFML_COLLISION_H

#include "GameObject.h"

class Collision
{
 public:
  Collision();
  ~Collision();
  enum class Type // we use an enum because it can return multiple different states that we can use later
    // its a class so we can use it multiple times. it saves time!
  { TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    NONE, };
  Type gameobjectCheck(GameObject& affector, GameObject& affected);
  Type windowCheck(GameObject& affector, sf::RenderWindow& window);
};

#endif // PLATFORMERSFML_COLLISION_H
