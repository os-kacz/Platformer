#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window), player(window, interface), interface(window)
{
  srand(time(NULL));
  countTiles();
  for (int i = 0; i < walkable_tiles; i++)
  {
    platform[i] = new Platform;
    platform[i]->initPlatform();
  }
  for (int j = 0; j < hazard_count; j++)
  {
    hazard[j] = new Hazard;
    hazard[j]->initHazard();
  }
//  for (int k = 0; k < collectible_count; k++)
//  {
//    collectible[k] = new Collectible;
//    collectible[k]->initCollectible();
//  }
}

Game::~Game()
{
  for (auto & _platform : platform)
  {
    delete _platform;
    _platform = nullptr;
  }
  for (auto & _hazard : hazard)
  {
    delete _hazard;
    _hazard = nullptr;
  }
}

bool Game::init()
{
  std::cout << "hazards: " << hazard_count << std::endl;
  if (interface.initText() && player.initPlayer())
  {
    generateLevel();
    return true;
  }
  else
    return false;
}

void Game::update(float dt)
{
  player.update(dt);
  windowCollision();
  int no_collision_count = 0;
  int invisible_tiles = 0;
  for (int i = 0; i < walkable_tiles; i++)
  {
    if (platform[i]->visible)
    {
      if (collision.gameobjectCheck(player, *platform[i]) != Collision::Type::NONE)
      {
        no_collision_count--;
        playerPlatformCollision(*platform[i]);
      }
      else if (
        collision.gameobjectCheck(player, *platform[i]) ==
        Collision::Type::NONE)
      {
        no_collision_count++;
        if (no_collision_count == walkable_tiles - invisible_tiles)
        {
          interface.collisions.setString("None");
          player.on_ground = false;
        }
      }
    }
    else if (!platform[i]->visible)
      invisible_tiles++;
  }
  debugText();
}

void Game::render()
{
  for (int i = 0; i < walkable_tiles; i++)
  {
    if (platform[i]->visible)
      window.draw(*platform[i]->getSprite());
  }
  for (int j = 0; j < hazard_count; j++)
  {
    window.draw(*hazard[j]->getSprite());
  }
  window.draw(*player.getSprite());
  window.draw(interface.debug);
  window.draw(interface.collisions);
  window.draw(interface.jump_window);
}

void Game::keyPressed(sf::Event event)
{
  player.move(event);
  if (event.key.code == sf::Keyboard::Escape)
    window.close();
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
      if (!player.on_ground)
      {
        interface.collisions.setString("Top");
        player.on_ground = true;
        player.direction.y = 0;
        player.getSprite()->setPosition(
          player.top_l_x,
          f_platform.top_l_y - player.getSprite()->getGlobalBounds().height);
      }
      break;
    }
    case (Collision::Type::BOTTOM):
    {
      interface.collisions.setString("Bottom");
      player.is_jumping  = false;
      player.direction.y = 0;
      player.getSprite()->setPosition(player.top_l_x, f_platform.bot_l_y);
      break;
    }
    case (Collision::Type::LEFT):
    {
      interface.collisions.setString("Left");
      player.getSprite()->setPosition(
        f_platform.top_l_x - player.getSprite()->getGlobalBounds().width,
        player.top_l_y);
      if (player.direction.x > 0 && player.direction.y > 0)
      {
        player.is_jumping  = false;
        player.direction.y = 0.3;
      }
      break;
    }
    case (Collision::Type::RIGHT):
    {
      interface.collisions.setString("Right");
      player.getSprite()->setPosition(f_platform.top_r_x, player.top_l_y);
      if (player.direction.x < 0 && player.direction.y > 0)
      {
        player.is_jumping  = false;
        player.direction.y = 0.3;
      }
      break;
    }
    case (Collision::Type::NONE):
    {
      break;
    }
  }
}

void Game::windowCollision()
{
  switch (collision.windowCheck(player, window))
  {
    case Collision::Type::TOP:
    {
      player.is_jumping = false;
      player.getSprite()->setPosition(player.top_l_x,0);
      player.direction.y = 0;
      break;
    }
    case Collision::Type::BOTTOM:
    {
      player.getSprite()->setPosition(
        platform[spawn_tile]->getSprite()->getPosition().x,
        platform[spawn_tile]->getSprite()->getPosition().y);
      break;
    }
    case Collision::Type::LEFT:
    {
      player.getSprite()->setPosition(0,player.top_l_y);
      break;
    }
    case Collision::Type::RIGHT:
    {
      player.getSprite()->setPosition(
        window.getSize().x - player.getSprite()->getGlobalBounds().width,
        player.top_l_y);
      break;
    }
    case Collision::Type::NONE:
    {
      break;
    }
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

bool Game::calibratePunchCard()
{
  level.loadFromFile("Data/Images/levelone.png");
  for (int i = 0; i < 6; i++)
  {
    sf::Color color = level.getPixel(i,13);
    if (color != sf::Color::Red
        && color != sf::Color::Yellow
        && color != sf::Color::Green
        && color != sf::Color::White
        && color != sf::Color::Black
        && color != sf::Color::Blue)
      return false;
  }
  return true;
}

void Game::countTiles()
{
  if (calibratePunchCard())
  {
    std::cout << "level punch card calibrated\n";
    for (int x_gen = 0; x_gen < tile_column; x_gen++)
    {
      for (int y_gen = 0; y_gen < tile_row; y_gen++)
      {
        sf::Color tile_type = level.getPixel(x_gen, y_gen);
        if (tile_type == sf::Color::Black || tile_type == sf::Color::Blue)
          walkable_tiles++;
        if (tile_type == sf::Color::Red)
          hazard_count++;
        if (tile_type == sf::Color::Yellow)
          collectible_count++;
      }
    }
  }
  else
    std::cout << "level punch card failure\n";
}

void Game::generateLevel()
{
  int walkable_accum = 0;
  int hazard_accum = 0;
  sf::Color tile_type;
  for (int x_gen = 0; x_gen < tile_column; x_gen++)
  {
    for (int y_gen = 0; y_gen < tile_row; y_gen++)
    {
      tile_type = level.getPixel(x_gen, y_gen);
      if (tile_type == sf::Color::Black)
      {
        platform[walkable_accum]->getSprite()->setPosition(
          x_gen * platform[walkable_accum]->getSprite()->getGlobalBounds().width,
          y_gen * platform[walkable_accum]->getSprite()->getGlobalBounds().height);
        walkable_accum++;
      }
      if (tile_type == sf::Color::Blue)
      {
        platform[walkable_accum]->getSprite()->setPosition(
          x_gen * platform[walkable_accum]->getSprite()->getGlobalBounds().width,
          y_gen * platform[walkable_accum]->getSprite()->getGlobalBounds().height);
        platform[walkable_accum]->visible = false;
        player.getSprite()->setPosition(
          platform[walkable_accum]->getSprite()->getPosition().x,
          platform[walkable_accum]->getSprite()->getPosition().y);
        spawn_tile = walkable_accum;
        walkable_accum++;
      }
      if (tile_type == sf::Color::Red)
      {
        hazard[hazard_accum]->getSprite()->setPosition(
          x_gen * hazard[hazard_accum]->getSprite()->getGlobalBounds().width,
          y_gen * hazard[hazard_accum]->getSprite()->getGlobalBounds().height);
        tile_type = level.getPixel(x_gen - 1, y_gen);
        if (tile_type == sf::Color::Black)
        {
          hazard[hazard_accum]->getSprite()->rotate(90);
          hazard[hazard_accum]->getSprite()->setPosition(
            (x_gen + 1) * hazard[hazard_accum]->getSprite()->getGlobalBounds().width,
            hazard[hazard_accum]->getSprite()->getPosition().y);
          hazard_accum++;
          continue;
        }
        tile_type = level.getPixel(x_gen + 1, y_gen);
        if (tile_type == sf::Color::Black)
        {
          hazard[hazard_accum]->getSprite()->rotate(-90);
          hazard[hazard_accum]->getSprite()->setPosition(
            (x_gen) * hazard[hazard_accum]->getSprite()->getGlobalBounds().width,
            (y_gen + 1) * hazard[hazard_accum]->getSprite()->getGlobalBounds().height);
        }
        hazard_accum++;
      }
    }
  }
}