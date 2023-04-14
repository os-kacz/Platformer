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
 private:
  sf::Texture texture;
};

#endif // PLATFORMERSFML_HAZARD_H
