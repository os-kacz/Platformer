#include "Camera.h"

Camera::Camera(GameObject& player, sf::RenderWindow& window) : player(player), window(window)
{
  camera = new sf::View();
  camera->setSize(window.getSize().x, window.getSize().y);
  camera->zoom(0.6);
  background.initialiseSprite(texture,"Data/Images/dirt_background.png");
  background.getSprite()->setColor(sf::Color(140,91,45,255));
  texture.setRepeated(true);
  background.getSprite()->setTextureRect(sf::IntRect(0,0,2000,2000));
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
  camera->setCenter(int(player.top_l_x), int(player.top_l_y));
  cameraClamp();
  // parallax effect for background
  background.getSprite()->setPosition(
    (camera->getCenter().x - 1000) * 0.3,
    (camera->getCenter().y - 1000) * 0.3);
}

sf::View* Camera::getCamera()
{
  return camera;
}
void Camera::cameraClamp() // clamps camera to window
{
  if (((camera->getCenter().x - (camera->getSize().x) / 2)) < 0)
    camera->setCenter(0 + (camera->getSize().x / 2), camera->getCenter().y);

  if (((camera->getCenter().x + (camera->getSize().x / 2)) > window.getSize().x))
    camera->setCenter(window.getSize().x - (camera->getSize().x / 2), camera->getCenter().y);

  if (((camera->getCenter().y + (camera->getSize().y / 2)) > window.getSize().y))
    camera->setCenter(camera->getCenter().x,window.getSize().y - (camera->getSize().y / 2));

  if (((camera->getCenter().y - (camera->getSize().y / 2)) < 0))
    camera->setCenter(camera->getCenter().x, 0 + (camera->getSize().y / 2));
}
