#ifndef PLATFORMERSFML_PLAYER_H
#define PLATFORMERSFML_PLAYER_H

#include <SFML/Audio.hpp>
#include "GameObject.h"
#include "Collision.h"
#include "Interface.h"

class Player : public GameObject
{
 public:
  Player(sf::RenderWindow& game_window);
  ~Player();
  bool initPlayer();
  void update(float dt);
  void move(sf::Event& event);
  void stop(sf::Event& event);
  void playCollideSFX(Collision::Type collision);
  void playGemSFX();
  void playHurtSFX();
  bool on_ground;
  bool is_jumping;
 private:
  sf::Texture player_texture_1;
  sf::Texture player_texture_2;
  sf::RenderWindow& window;
  sf::Clock jump_window;
  sf::Clock sound_window;
  sf::Clock animation_step;
  sf::SoundBuffer jump_buffer[2];
  sf::SoundBuffer walk_buffer[2];
  sf::SoundBuffer gem_buffer;
  sf::SoundBuffer hurt_buffer;
  sf::Sound jump_sfx_1;
  sf::Sound jump_sfx_2;
  sf::Sound walk_sfx_1;
  sf::Sound walk_sfx_2;
  sf::Sound gem_sfx;
  sf::Sound hurt_sfx;
  float speed_multiplier = 1.4;
  float jump_power = 5;
  float terminal_velocity = 4;
  bool played = false;
  bool texture_swap       = true;
  void checkJump();
  void jumping();
  void falling();

};

#endif // PLATFORMERSFML_PLAYER_H
