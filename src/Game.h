#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Collision.h"
#include "Interface.h"
#include "Hazard.h"
#include "Collectible.h"

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
  const static int tile_column = 20;
  const static int tile_row = 13;
  const static int platform_count = tile_column * tile_row;
  int walkable_tiles = 0;
  int hazard_count = 0;
  int collectible_count = 0;
  sf::RenderWindow& window;
  sf::Image level;
  Interface interface;
  Player player;
  Platform* platform[platform_count];
  Hazard* hazard[20];
  Collectible* collectible[10];
  Collision collision;
  void generateLevel();
  void countTiles();
  int spawn_tile;
  struct CollisionCount{int none_colliding; int uninteractible;} ;
  CollisionCount platformCollisionCount(Platform& f_platform, int none_colliding, int uninteractible);
  void playerPlatformCollision(Platform& f_platform);
  void playerHazardCollision(Hazard& f_hazard);
  void windowCollision();
  void debugText();
  bool calibratePunchCard();

};

#endif // PLATFORMER_GAME_H
