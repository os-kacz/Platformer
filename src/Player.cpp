#include "Player.h"

Player::Player(sf::RenderWindow& game_window) : window(game_window)
{
  speed *= speed_multiplier;
}

Player::~Player(){}

bool Player::initPlayer()
{
  getSprite()->setPosition(500,window.getSize().y - 500);
  direction.y = gravity;
  getSprite()->setScale(0.1,0.1);
  return initialiseSprite(player_texture,
                          "Data/Images/placeholder.png");
}

void Player::update(float dt)
{
  getSprite()->move(direction.x * dt * speed, direction.y * dt * speed);
  getBoundingBox();
  windowCollision();
  checkJump();
}

void Player::move(sf::Event& event)
{
  if (event.key.code == sf::Keyboard::A)
    direction.x = -2;
  if (event.key.code == sf::Keyboard::D)
    direction.x = 2;
  if (jump_window.getElapsedTime().asSeconds() <= 0.15 && !is_jumping)
  {
    if (event.key.code == sf::Keyboard::Space)
    {
      getSprite()->setPosition(top_l_x, top_l_y - 1);
      direction.y = jump_power * -1;
      is_jumping = true;
      on_ground = false;
    }
  }
}

void Player::checkJump()
{
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

void Player::windowCollision()
{
  switch (collision.windowCheck(*this, window))
  {
    case Collision::Type::TOP:
    {
      is_jumping = false;
      getSprite()->setPosition(top_l_x,0);
      direction.y = 0;
      break;
    }
    case Collision::Type::BOTTOM:
    {
      break;
    }
    case Collision::Type::LEFT:
    {
      break;
    }
    case Collision::Type::RIGHT:
    {
      break;
    }
    case Collision::Type::NONE:
    {
      break;
    }
  }
}

void Player::stop(sf::Event& event)
{
  if (event.key.code == sf::Keyboard::A && direction.x < 0)
    direction.x = 0;
  if (event.key.code == sf::Keyboard::D && direction.x > 0)
    direction.x = 0;
}