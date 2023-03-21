#ifndef PLATFORMERSFML_PLAYER_H
#define PLATFORMERSFML_PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
 public:
  Player(sf::RenderWindow& window);
  ~Player();
  bool initPlayer();
  void update();
  void move(sf::Event& event);
  void stop(sf::Event& event);
 private:
  float speed_multiplier = 4;
  sf::Texture player_texture;
  sf::RenderWindow& window;
};

#endif // PLATFORMERSFML_PLAYER_H
