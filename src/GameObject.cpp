#include "GameObject.h"

GameObject::GameObject()
{
  sprite = new sf::Sprite();
}

GameObject::~GameObject()
{
  if (sprite != nullptr)
  {
    delete sprite;
    sprite = nullptr;
  }
}

bool GameObject::initialiseSprite(sf::Texture& texture, std::string filename)
{
  if (!texture.loadFromFile(filename)){
    std::cout << "Error loading from" << filename << std::endl;
    return false;
  }
  sprite->setTexture(texture);
  return true;
}

sf::Sprite* GameObject::getSprite()
{
  return sprite;
}

void GameObject::getBoundingBox()
{
  top_l_x = sprite->getPosition().x;
  top_r_x = top_l_x + sprite->getGlobalBounds().width;
  top_l_y = sprite->getPosition().y;
  bot_l_y = top_l_y + sprite->getGlobalBounds().height;
}
