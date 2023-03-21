#include "Player.h"

Player::Player(sf::RenderWindow& game_window) : window(game_window)
{
  speed *= speed_multiplier;
}

Player::~Player(){}

bool Player::initPlayer()
{
  getSprite()->setPosition((window.getSize().x / 2) - top_r_x ,
                           window.getSize().y - top_l_y);
  getSprite()->setScale(10,10);
  return initialiseSprite(player_texture,
                          "Data/Images/placeholder.png");
}