#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Collision.h"
#include "Interface.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
 private:
  const static int platform_count = 30;
  sf::RenderWindow& window;
  Interface interface;
  Player player;
  Platform* platform[platform_count];
  Collision collision;
  void playerPlatformCollision(Platform& f_platform);
  void platformSpawnGroups();
  int platform_accum = 0;
  int no_collision_count = 0;
  void debugText();
};

#endif // PLATFORMER_GAME_H
