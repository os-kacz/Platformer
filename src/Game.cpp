#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window), player(window)
{
  srand(time(NULL));
  for (auto & _platform : platform)
  {
    _platform = new Platform;
    _platform->initPlatform();
  }
}

Game::~Game()
{
  for (auto & _platform : platform)
  {
    delete _platform;
    _platform = nullptr;
  }
}

bool Game::init()
{
  platformSpawnGroups();
  for (auto & _platform : platform)
    _platform->initPlatform();
  return player.initPlayer();
}

void Game::update(float dt)
{
  player.update(dt);
  for (auto & _platform : platform)
  {
    playerPlatformCollision(*_platform);
    if (collision.gameobjectCheck(player, *_platform) == Collision::Type::NONE)
      player.on_ground = false;
  }
}

void Game::render()
{
  window.draw(*player.getSprite());
  for (auto & _platform : platform)
    window.draw(*_platform->getSprite());
}

void Game::keyPressed(sf::Event event)
{
  player.move(event);
}

void Game::keyReleased(sf::Event event)
{
  player.stop(event);
}

void Game::playerPlatformCollision(Platform& f_platform)
{
  player.getBoundingBox();
  f_platform.getBoundingBox();
  switch (collision.gameobjectCheck(player, f_platform))
  {
    case (Collision::Type::TOP):
    {
      std::cout << "TOP" << std::endl;
      player.on_ground = true;
      //player.is_jumping = false;
      player.direction.y = 0;
      player.getSprite()->setPosition(
        player.top_l_x,
        f_platform.top_l_y - player.getSprite()->getGlobalBounds().height);
      break;
    }
    case (Collision::Type::BOTTOM):
    {
      player.is_jumping = false;
      player.direction.y = 0;
      player.getSprite()->setPosition(player.top_l_x, f_platform.bot_l_y);
      break;
    }
    case (Collision::Type::LEFT):
    {
      player.is_jumping = false;
      player.getSprite()->setPosition(
        f_platform.top_l_x - player.getSprite()->getGlobalBounds().width,
        player.top_l_y);
      if (player.direction.x > 0)
        player.direction.y = 0.1;
      break;
    }
    case (Collision::Type::RIGHT):
    {
      player.is_jumping = false;
      player.getSprite()->setPosition(f_platform.top_r_x, player.top_l_y);
      if (player.direction.x < 0)
        player.direction.y = 0.1;
      break;
    }
    case (Collision::Type::NONE):
    {
      break;
    }
  }
}
void Game::platformSpawnGroups()
{
  for (int first = 0; first < 10; first++)
  {
    platform[platform_accum]->getSprite()->setPosition(
      0 + (platform[platform_accum]->getSprite()->getGlobalBounds().width * first+1),
      (window.getSize().y - platform[platform_accum]->getSprite()->getGlobalBounds().height));
    platform_accum++;
  }
  for (int second = 0; second < 2; second++)
  {
    platform[platform_accum]->getSprite()->setPosition(
      0 + (platform[platform_accum]->getSprite()->getGlobalBounds().width * second+1),
      300);
    platform_accum++;
  }
}
