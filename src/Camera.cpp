#include "Camera.h"

Camera::Camera(GameObject& player, sf::RenderWindow& window) : player(player), window(window)
{
  camera = new sf::View();
  camera->setSize(window.getSize().x, window.getSize().y);
  camera->zoom(0.7);
}

Camera::~Camera()
{
  if (camera != nullptr)
  {
    delete camera;
    camera = nullptr;
  }
}

void Camera::followPlayer()
{
  camera->setCenter(player.top_l_x, player.top_l_y);
}

sf::View* Camera::getCamera()
{
  return camera;
}
