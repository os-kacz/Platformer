#ifndef PLATFORMERSFML_HAZARD_H
#define PLATFORMERSFML_HAZARD_H

#include "SFML/Graphics.hpp"
#include "GameObject.h"

class Hazard : public GameObject
{
 public:
  Hazard();
  ~Hazard();
  bool initHazard();
  void update(GameObject& affector);
  void initLeftTexture();
  bool facing_left;
  bool on_ground = false;
 private:
  sf::Texture texture;
  sf::Texture texture_left;
};

#endif // PLATFORMERSFML_HAZARD_H
