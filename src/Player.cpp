#include "Player.h"

Player::Player(sf::RenderWindow& game_window, Interface& debug) : window(game_window), debug(debug)
{
  speed *= speed_multiplier;
}

Player::~Player(){}

bool Player::initPlayer()
{
  getSprite()->setPosition(500,window.getSize().y - 500);
  direction.y = gravity;
  getSprite()->setScale(1.2,1.2);
  return initialiseSprite(player_texture,
                          "Data/Images/kenney_pixelplatformer/Characters/character_0000.png");
}

void Player::update(float dt)
{
  getSprite()->move(direction.x * dt * speed, direction.y * dt * speed);
  updateBoundingBox();
  checkJump();
}

void Player::move(sf::Event& event)
{
  if (event.key.code == sf::Keyboard::A)
    direction.x = -2;
  if (event.key.code == sf::Keyboard::D)
    direction.x = 2;
  if (jump_window.getElapsedTime().asSeconds() < 0.15 && !is_jumping)
  {
    if (event.key.code == sf::Keyboard::Space)
    {
      getSprite()->setPosition(top_l_x, top_l_y - 2);
      direction.y = jump_power * -1;
      is_jumping = true;
      on_ground = false;
    }
  }
}

void Player::checkJump()
{
  debug.jump_window.setPosition(0,debug.collisions.getPosition().y + debug.collisions.getGlobalBounds().height + 12);
  debug.jump_window.setString(std::to_string(jump_window.getElapsedTime().asSeconds()));
  if (jump_window.getElapsedTime().asSeconds() > 0.1 && on_ground)
    jump_window.restart();

  if (!on_ground)
  {
    if (is_jumping)
      jumping();
    else
      falling();
  }
}

void Player::jumping()
{
  if (direction.y > 0)
    is_jumping = false;
  else
    direction.y += velocity;
}

void Player::falling()
{
  direction.y += velocity;
  if (direction.y > terminal_velocity)
    direction.y = terminal_velocity;
}

void Player::stop(sf::Event& event)
{
  if (event.key.code == sf::Keyboard::A && direction.x < 0)
    direction.x = 0;
  if (event.key.code == sf::Keyboard::D && direction.x > 0)
    direction.x = 0;
}