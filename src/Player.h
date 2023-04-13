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
  bool on_ground;
  bool is_jumping;
 private:
  sf::Texture player_texture;
  sf::RenderWindow& window;
  Collision collision;
  float speed_multiplier = 1.4;
  float jump_power = 4;
  float terminal_velocity = 4;
  void checkJump();
  void jumping();
  void falling();
  void windowCollision();
  sf::Clock jump_window;
};

#endif // PLATFORMERSFML_PLAYER_H
