#ifndef PLATFORMERSFML_CAMERA_H
#define PLATFORMERSFML_CAMERA_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Camera
{
 public:
  Camera(GameObject& player, sf::RenderWindow& window);
  virtual ~Camera();
  void followPlayer();
  sf::View* getCamera();
 private:
  sf::View* camera = nullptr;
  GameObject& player;
  sf::RenderWindow& window;
  float y_diff;
};

#endif // PLATFORMERSFML_CAMERA_H
