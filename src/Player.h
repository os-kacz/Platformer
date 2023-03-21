#ifndef PLATFORMERSFML_PLAYER_H
#define PLATFORMERSFML_PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
 public:
  Player(sf::RenderWindow& window);
  ~Player();
  bool initPlayer();
  void update(float dt);
  void move(sf::Event& event);
  void stop(sf::Event& event);
 private:
  sf::Texture player_texture;
  sf::RenderWindow& window;
  float speed_multiplier = 4;
  float jump_height = 30;
  bool on_ground;
};

#endif // PLATFORMERSFML_PLAYER_H
