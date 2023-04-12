#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window), player(window), interface(window)
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
  generateLevel();
  platformSpawnGroups();
  interface.initText();
  for (auto & _platform : platform)
    _platform->initPlatform();
  return player.initPlayer();
}

void Game::update(float dt)
{
  player.update(dt);
  no_collision_count = 0;
  for (auto & _platform : platform)
  {
    if (collision.gameobjectCheck(player, *_platform) != Collision::Type::NONE)
    {
      no_collision_count--;
      playerPlatformCollision(*_platform);
    }
    else
    {
      no_collision_count++;
      if (no_collision_count == platform_count)
      {
        interface.collisions.setString("None");
        player.on_ground = false;
      }
    }
  }
  debugText();
}

void Game::render()
{
  window.draw(*player.getSprite());
  for (auto & _platform : platform)
    window.draw(*_platform->getSprite());
  window.draw(interface.debug);
  window.draw(interface.collisions);
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
      interface.collisions.setString("Top");
      player.on_ground = true;
      player.direction.y = 0;
      player.getSprite()->setPosition(
        player.top_l_x,
        f_platform.top_l_y - player.getSprite()->getGlobalBounds().height);
      break;
    }
    case (Collision::Type::BOTTOM):
    {
      interface.collisions.setString("Bottom");
      player.is_jumping = false;
      player.direction.y = 0;
      player.getSprite()->setPosition(player.top_l_x, f_platform.bot_l_y);
      break;
    }
    case (Collision::Type::LEFT):
    {
      interface.collisions.setString("Left");
      player.is_jumping = false;
      player.getSprite()->setPosition(
        f_platform.top_l_x - player.getSprite()->getGlobalBounds().width,
        player.top_l_y);
      if (player.direction.x > 0 && player.direction.y > 0)
        player.direction.y = 0.1;
      break;
    }
    case (Collision::Type::RIGHT):
    {
      interface.collisions.setString("Right");
      player.getSprite()->setPosition(f_platform.top_r_x, player.top_l_y);
      if (player.direction.x < 0 && player.direction.y > 0)
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
  for (int first = 0; first < 20; first++)
  {
    platform[platform_accum]->getSprite()->setPosition(
      0 + (platform[platform_accum]->getSprite()->getGlobalBounds().width * first+1),
      (window.getSize().y - platform[platform_accum]->getSprite()->getGlobalBounds().height));
    platform_accum++;
  }
  for (int second = 0; second < 4; second++)
  {
    platform[platform_accum]->getSprite()->setPosition(
      0 + (platform[platform_accum]->getSprite()->getGlobalBounds().width * second+1),
      500);
    platform_accum++;
  }
  for (int third = 0; third < 6; third++)
  {
    platform[platform_accum]->getSprite()->setPosition(
      400 + (platform[platform_accum]->getSprite()->getGlobalBounds().width * third+1),
      300);
    platform_accum++;
  }
  for (int fourth = 0; fourth < 13; fourth++)
  {
    platform[platform_accum]->getSprite()->setPosition(
      0,
      (platform[platform_accum]->getSprite()->getGlobalBounds().height * fourth+1));
    platform_accum++;
  }
}

void Game::debugText()
{
  if (player.on_ground && !player.is_jumping)
    interface.debug.setString("On Ground\nFalling");
  else if (player.on_ground && player.is_jumping)
    interface.debug.setString("On Ground\nJumping");
  else if (!player.on_ground && !player.is_jumping)
    interface.debug.setString("In Air\nFalling");
  else if (!player.on_ground && player.is_jumping)
    interface.debug.setString("In Air\nJumping");
  interface.collisions.setPosition(0,interface.debug.getPosition().y + interface.debug.getGlobalBounds().height);
}
bool Game::calibrateLevelPunchCard()
{
  level.loadFromFile("Data/Images/levelone.png");
  for (int i = 0; i < 5; i++)
  {
    sf::Color color = level.getPixel(i,13);
    if (color != sf::Color::Red
        && color != sf::Color::Yellow
        && color != sf::Color::Green
        && color != sf::Color::White
        && color != sf::Color::Black)
      return false;
  }
  return true;
}
void Game::generateLevel()
{
  if (calibrateLevelPunchCard())
  {
    std::cout << "level punch card calibrated";
  }
  else
    std::cout << "level punch card failure";
}
