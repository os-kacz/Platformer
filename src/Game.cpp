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
  for (int k = 0; k < collectible_count; k++)
  {
    collectible[k] = new Collectible;
    collectible[k]->initCollectible();
  }
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
  for (auto & _collectible : collectible)
  {
    delete _collectible;
    _collectible = nullptr;
  }
}

bool Game::init()
{
  std::cout << "tiles placed: " << walkable_tiles << "/120" << std::endl;
  std::cout << "hazards: " << hazard_count << "/20" << std::endl;
  std::cout << "collectibles: " << collectible_count << "/10" << std::endl;
  gamestate = MAIN_MENU;
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
  if (player.health < 0)
  {
    gamestate = GAMEOVER;
  }
  if (gamestate == PLAYGAME)
  {
    player.update(dt);
    windowCollision();
    int no_collision_count = 0;
    int invisible_tiles    = 0;
    for (int i = 0; i < walkable_tiles; i++)
    {
      CollisionCount returned_values = platformCollisionCount(
        *platform[i], no_collision_count, invisible_tiles);
      no_collision_count = returned_values.none_colliding;
      invisible_tiles    = returned_values.uninteractible;
    }
    for (int j = 0; j < hazard_count; j++)
    {
      playerHazardCollision(*hazard[j]);
    }
    for (int k = 0; k < collectible_count; k++)
    {
      if (
        collision.gameobjectCheck(player, *collectible[k]) !=
        Collision::Type::NONE && collectible[k]->visible)
      {
        collectible[k]->visible = false;
        current_collectibles++;
        if (current_collectibles == collectible_count)
        {
          gamestate = GAMEWIN;
        }
      }
    }
    debugText();
  }
}

void Game::render()
{
  switch (gamestate)
  {
    case MAIN_MENU:
    {

      break;
    }
    case PLAYGAME:
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
      for (int k = 0; k < collectible_count; k++)
      {
        if (collectible[k]->visible)
          window.draw(*collectible[k]->getSprite());
      }
      window.draw(*player.getSprite());
      window.draw(interface.debug);
      window.draw(interface.collisions);
      window.draw(interface.jump_window);
      break;
    }
    case GAMEWIN:
    {

      break;
    }
    case GAMEOVER:
    {

      break;
    }
  }
}

void Game::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Enter && gamestate == MAIN_MENU)
    gamestate = PLAYGAME;

  if (gamestate == PLAYGAME)
  {
    player.move(event);
    if (event.key.code == sf::Keyboard::Escape)
    {
      window.close();
      std::cout << "Deconstructing...\n";
    }
  }
}

void Game::keyReleased(sf::Event event)
{
  if (gamestate == PLAYGAME)
  {
    player.stop(event);
  }
}

Game::CollisionCount Game::platformCollisionCount(Platform& f_platform, int none_colliding, int uninteractible)
{
  if (f_platform.visible)
  {
    if (collision.gameobjectCheck(player, f_platform) != Collision::Type::NONE)
    {
      none_colliding--;
      playerPlatformCollision(f_platform);
    }
    else if (
      collision.gameobjectCheck(player, f_platform) ==
      Collision::Type::NONE)
    {
      none_colliding++;
      if (none_colliding == walkable_tiles - uninteractible)
      {
        interface.collisions.setString("None");
        player.on_ground = false;
      }
    }
  }
  else if (!f_platform.visible)
    uninteractible++;
  CollisionCount accum = { none_colliding, uninteractible };
  return accum;
}

void Game::playerPlatformCollision(Platform& f_platform)
{
  f_platform.updateBoundingBox();
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

void Game::playerHazardCollision(Hazard& f_hazard)
{
  f_hazard.updateBoundingBox();
  if (collision.gameobjectCheck(player, f_hazard) != Collision::Type::NONE)
  {
    if (f_hazard.facing_left && !f_hazard.on_ground
        && player.top_r_x > f_hazard.top_l_x + (f_hazard.getSprite()->getGlobalBounds().width / 2)
        ||!f_hazard.facing_left && !f_hazard.on_ground
             && player.top_l_x < f_hazard.top_r_x - (f_hazard.getSprite()->getGlobalBounds().width / 2)
        ||f_hazard.on_ground && player.bot_l_y > f_hazard.top_l_y + (f_hazard.getSprite()->getGlobalBounds().height / 2))
    {
      player.health--;
      player.getSprite()->setPosition(
        platform[spawn_tile]->getSprite()->getPosition().x,
        platform[spawn_tile]->getSprite()->getPosition().y);
    }
//    else if (!f_hazard.facing_left && !f_hazard.on_ground
//             && player.top_l_x < f_hazard.top_r_x - (f_hazard.getSprite()->getGlobalBounds().width / 2))
//    {
//      player.getSprite()->setPosition(
//        platform[spawn_tile]->getSprite()->getPosition().x,
//        platform[spawn_tile]->getSprite()->getPosition().y);
//    }
//    else if (f_hazard.on_ground && player.bot_l_y > f_hazard.top_l_y + (f_hazard.getSprite()->getGlobalBounds().height / 2))
//    {
//      player.getSprite()->setPosition(
//        platform[spawn_tile]->getSprite()->getPosition().x,
//        platform[spawn_tile]->getSprite()->getPosition().y);
//    }
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
  levelone.loadFromFile("Data/Images/levelone.png");
  for (int i = 0; i < 6; i++)
  {
    sf::Color color = levelone.getPixel(i,13);
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
    std::cout << "levelone punch card calibrated\n";
    for (int x_gen = 0; x_gen < tile_column; x_gen++)
    {
      for (int y_gen = 0; y_gen < tile_row; y_gen++)
      {
        sf::Color tile_type = levelone.getPixel(x_gen, y_gen);
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
    std::cout << "levelone punch card failure\n";
}

void Game::generateLevel()
{
  int walkable_accum = 0;
  int hazard_accum = 0;
  int collect_accum = 0;
  sf::Color tile_type;
  for (int x_gen = 0; x_gen < tile_column; x_gen++)
  {
    for (int y_gen = 0; y_gen < tile_row; y_gen++)
    {
      tile_type = levelone.getPixel(x_gen, y_gen);
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
        tile_type = levelone.getPixel(x_gen - 1, y_gen);
        if (tile_type == sf::Color::Black)
        {
          hazard[hazard_accum]->initLeftTexture();
          hazard[hazard_accum]->facing_left = false;
          hazard_accum++;
          continue;
        }
        tile_type = levelone.getPixel(x_gen + 1, y_gen);
        if (tile_type == sf::Color::Black)
        {
          hazard[hazard_accum]->initLeftTexture();
          hazard[hazard_accum]->getSprite()->setTextureRect(
            sf::IntRect(
              hazard[hazard_accum]->getSprite()->getLocalBounds().width,
              0,
              -hazard[hazard_accum]->getSprite()->getLocalBounds().width,
              hazard[hazard_accum]->getSprite()->getLocalBounds().height));
          hazard[hazard_accum]->facing_left = true;
        }
        else
          hazard[hazard_accum]->on_ground = true;
        hazard_accum++;
      }
      if (tile_type == sf::Color::Yellow)
      {
        collectible[collect_accum]->getSprite()->setPosition(
          x_gen * collectible[collect_accum]->getSprite()->getGlobalBounds().width,
          y_gen * collectible[collect_accum]->getSprite()->getGlobalBounds().height);
        collect_accum++;
      }
    }
  }
}