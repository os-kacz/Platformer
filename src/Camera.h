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
  GameObject background;
 private:
  void cameraClamp();
  sf::View* camera = nullptr;
  GameObject& player;
  sf::RenderWindow& window;
  sf::Texture texture;
};

#endif // PLATFORMERSFML_CAMERA_H
