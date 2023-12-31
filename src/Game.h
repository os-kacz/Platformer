#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Collision.h"
#include "Interface.h"
#include "Hazard.h"
#include "Collectible.h"
#include "Camera.h"

class Game
{
 public:
  Game(sf::RenderWindow& game_window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
 private:
  enum{
    MAINMENU, PLAYGAME, GAMEWIN, GAMEOVER} gamestate;
  const static int tile_column = 20;
  const static int tile_row = 13;
  int walkable_tiles = 0;
  int hazard_count = 0;
  int collectible_count = 0;
  int current_collectibles = 0;
  sf::RenderWindow& window;
  sf::Image levelone;
  sf::Image levelstep;
  sf::Image leveldom;
  sf::Image* current_level;
  Interface interface;
  Player player;
  Platform* platform[120];
  Hazard* hazard[20];
  Collectible* collectible[10];
  Collision collision; // collision class! very helpful, read collision.h and collision.cpp
  Camera camera;
  void restartGame();
  void playerPlatformCollision(Platform& f_platform);
  void playerHazardCollision(Hazard& f_hazard);
  void windowCollision();
  bool calibrateLevelOne();
  bool calibrateLevelDom();
  bool calibrateLevelStep();
  void countTiles(sf::Image& level);
  int spawn_tile;
  void generateLevel(sf::Image& level);
  void allocateObjectPools();
  void changeLevel();
  int level_choice = 1;
};

#endif // PLATFORMER_GAME_H
