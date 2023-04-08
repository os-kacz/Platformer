#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window), player(window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  if (player.initPlayer() && platform.initPlatform())
    return true;
  else
    return false;
}

void Game::update(float dt)
{
  player.update(dt);
  platform.update();
  playerPlatformCollision();
}

void Game::render()
{
  window.draw(*player.getSprite());
  window.draw(*platform.getSprite());
}

void Game::keyPressed(sf::Event event)
{
  player.move(event);
}

void Game::keyReleased(sf::Event event)
{
  player.stop(event);
}

void Game::playerPlatformCollision()
{
  player.getBoundingBox();
  platform.getBoundingBox();
  switch (collision.gameobjectCheck(player, platform))
  {
    case (Collision::Type::TOP):
    {
      player.getSprite()->setPosition(
        player.top_l_x,
        platform.top_l_y - player.getSprite()->getGlobalBounds().height);
      player.on_ground = true;
      player.direction.y = 0;
      break;
    }
    case (Collision::Type::BOTTOM):
    {
      player.is_jumping = false;
      player.getSprite()->setPosition(player.top_l_x, platform.bot_l_y);
      player.direction.y = 0;
      break;
    }
    case (Collision::Type::LEFT):
    {
      player.is_jumping = false;
      player.getSprite()->setPosition(
        platform.top_l_x - player.getSprite()->getGlobalBounds().width,
        player.top_l_y);
      if (player.direction.x > 0)
        player.direction.y = 0.1;
      break;
    }
    case (Collision::Type::RIGHT):
    {
      player.is_jumping = false;
      player.getSprite()->setPosition(platform.top_r_x, player.top_l_y);
      if (player.direction.x < 0)
        player.direction.y = 0.1;
      break;
    }
    case (Collision::Type::NONE):
      break;
  }
}
