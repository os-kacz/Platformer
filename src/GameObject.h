#ifndef PLATFORMERSFML_GAMEOBJECT_H
#define PLATFORMERSFML_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vector.h"

class GameObject
{
 public:
  GameObject();
  ~GameObject();
  bool initialiseSprite(sf::Texture& texture, std::string filename);
  sf::Sprite* getSprite();
  bool visible = true;
  int health;
  float speed = 100;
  Vector direction = Vector(0, 0);
  void getBoundingBox();
  float top_l_x;
  float top_r_x;
  float top_l_y;
  float bot_l_y;
 protected:
  float gravity = 9.08;
  float velocity = 0.18;
 private:
  sf::Sprite* sprite = nullptr;
};

#endif // PLATFORMERSFML_GAMEOBJECT_H
