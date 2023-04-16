#ifndef PLATFORMERSFML_COLLECTIBLE_H
#define PLATFORMERSFML_COLLECTIBLE_H

#include "SFML/Graphics.hpp"
#include "GameObject.h"

class Collectible : public GameObject
{
 public:
  Collectible();
  ~Collectible();
  bool initCollectible();
 private:
  sf::Texture texture;
};

#endif // PLATFORMERSFML_COLLECTIBLE_H
