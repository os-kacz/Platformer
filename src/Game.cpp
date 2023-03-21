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
  if (player.initPlayer())
  {
    player.getBoundingBox();
    player.getSprite()->setPosition(
      500,
      window.getSize().y - player.getSprite()->getGlobalBounds().height);
    return true;
  }
  else
    return false;
}

void Game::update(float dt)
{
  player.update(dt);
}

void Game::render()
{
  window.draw(*player.getSprite());
}

void Game::keyPressed(sf::Event event)
{
  player.move(event);
}

void Game::keyReleased(sf::Event event)
{
  player.stop(event);
}