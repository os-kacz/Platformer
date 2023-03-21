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
  player.initPlayer();
  return true;
}

void Game::update(float dt)
{

}

void Game::render()
{
  window.draw(*player.getSprite());
}

void Game::keyPressed(sf::Event event)
{

}

void Game::keyReleased(sf::Event event)
{

}