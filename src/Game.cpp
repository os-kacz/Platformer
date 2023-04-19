#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window) : window(game_window), player(window), interface(window, camera),
  camera(player, window)
{
  calibrateLevelDom();
  countTiles(leveldom);
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
  gamestate = MAINMENU;
  if (interface.initText() && player.initPlayer())
  {
    generateLevel(leveldom);
    return true;
  }
  else
    return false;
}

void Game::update(float dt)
{
  interface.textInView();
  if (player.health == 0)
    gamestate = GAMEOVER;

  if (gamestate == PLAYGAME)
  {
    player.update(dt);
    camera.followPlayer();
    windowCollision();
    for (int i = 0; i < walkable_tiles; i++)
    {
      if (platform[i]->visible)
        playerPlatformCollision(*platform[i]);
    }
    for (int j = 0; j < hazard_count; j++)
    {
      playerHazardCollision(*hazard[j]);
    }
    for (int k = 0; k < collectible_count; k++)
    {
      if (collision.gameobjectCheck(player, *collectible[k]) !=
        Collision::Type::NONE && collectible[k]->visible)
      {
        collectible[k]->visible = false;
        current_collectibles++;
        player.playGemSFX();
        interface.score.setString(
          "Score: " + std::to_string(current_collectibles));
        if (current_collectibles == collectible_count)
          gamestate = GAMEWIN;
      }
    }
  }
}

void Game::render()
{
  switch (gamestate)
  {
    case MAINMENU:
    {
      window.draw(interface.main_text);
      break;
    }
    case PLAYGAME:
    {
      window.draw(*camera.background.getSprite());
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
      window.draw(interface.score);
      window.draw(interface.lives);
      window.setView(*camera.getCamera());
      break;
    }
    case GAMEWIN:
    {
      interface.main_text.setString("You got all the gems!\nPress enter to replay");
      window.draw(interface.main_text);
      break;
    }
    case GAMEOVER:
    {
      interface.main_text.setString("You lost all your lives\nPress enter to replay");
      window.draw(interface.main_text);
      break;
    }
  }
}

void Game::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Enter && gamestate != PLAYGAME)
    restartGame();

  if (gamestate == PLAYGAME)
    player.move(event);

  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close();
    std::cout << "Deconstructing...\n";
  }
}

void Game::keyReleased(sf::Event event)
{
  if (gamestate == PLAYGAME)
    player.stop(event);
}

void Game::restartGame()
{
  for (int i = 0; i < collectible_count; i++)
    collectible[i]->visible = true;
  player.health = 4;
  current_collectibles = 0;
  interface.score.setString(
    "Score: " + std::to_string(current_collectibles));
  interface.lives.setString("Lives: " + std::to_string(player.health));
  player.getSprite()->setPosition(
    platform[spawn_tile]->getSprite()->getPosition().x,
    platform[spawn_tile]->getSprite()->getPosition().y);
  gamestate = PLAYGAME;
}

void Game::playerPlatformCollision(Platform& f_platform)
{
  f_platform.updateBoundingBox();
  switch (collision.gameobjectCheck(player, f_platform))
  {
      // allows player to walk on top of platforms and jump again
    case (Collision::Type::TOP):
    {
      if (!player.on_ground)
      {
        player.on_ground = true;
        player.direction.y = 0;
        player.getSprite()->setPosition(
          player.top_l_x,
          f_platform.top_l_y - player.getSprite()->getGlobalBounds().height);
        player.playCollideSFX(Collision::Type::TOP);
      }
      break;
    }
      // stops player jumping and makes them fall down
    case (Collision::Type::BOTTOM):
    {
      player.is_jumping  = false;
      player.direction.y = 0;
      player.getSprite()->setPosition(player.top_l_x, f_platform.bot_l_y);
      player.playCollideSFX(Collision::Type::BOTTOM);
      break;
    }
      // left and right case allow players to grip onto blocks and slowly slide down
    case (Collision::Type::LEFT):
    {
      player.getSprite()->setPosition(
        f_platform.top_l_x - player.getSprite()->getGlobalBounds().width,
        player.top_l_y);
      player.playCollideSFX(Collision::Type::LEFT);
      if (player.direction.x > 0 && player.direction.y > 0)
      {
        player.is_jumping  = false;
        player.direction.y = 0.3;
      }
      break;
    }
    case (Collision::Type::RIGHT):
    {
      player.getSprite()->setPosition(f_platform.top_r_x, player.top_l_y);
      player.playCollideSFX(Collision::Type::RIGHT);
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
    // considers from what direction the player is coming from and when the player looks like when they physically touch the spike
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
      interface.lives.setString("Lives: " + std::to_string(player.health));
      player.playHurtSFX();
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
      player.health--;
      player.playHurtSFX();
      interface.lives.setString("Lives: " + std::to_string(player.health));
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
      player.playCollideSFX(Collision::Type::NONE);

      player.on_ground = false;
      // YEP, THIS ONE LINE JUST MADE 30% OF MY EFFORTS REDUNDANT
      // had difficulty detecting when player walked off a platform, this line solved that issue
      // keeping comment because it's funny
      break;
    }
  }
}

bool Game::calibrateLevelOne() // reads calibration strip to check if colours are readable
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

bool Game::calibrateLevelDom()
{
  leveldom.loadFromFile("Data/Images/leveldom.png");
  for (int i = 0; i < 6; i++)
  {
    sf::Color color = leveldom.getPixel(i,13);
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

void Game::countTiles(sf::Image& level) // counts what tiles need to be created for the object pools
{
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

void Game::generateLevel(sf::Image& level) // generates level based on pixel colour and neighbouring pixels
{
  int walkable_accum = 0;
  int hazard_accum = 0;
  int collect_accum = 0;
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
          hazard[hazard_accum]->initLeftTexture();
          hazard[hazard_accum]->facing_left = false;
          hazard_accum++;
          continue;
        }
        tile_type = level.getPixel(x_gen + 1, y_gen);
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