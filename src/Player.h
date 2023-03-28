#ifndef PLATFORMERSFML_PLAYER_H
#define PLATFORMERSFML_PLAYER_H

#include "GameObject.h"
#include "Collision.h"

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
  Collision collision;
  float speed_multiplier = 2;
  float jump_power = 6;
  bool on_ground;
  bool is_jumping;
  void checkJump();
  void jumping();
  void falling();
};

#endif // PLATFORMERSFML_PLAYER_H
