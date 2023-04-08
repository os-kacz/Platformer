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
  getSprite()->setScale(0.2,0.2);
  return initialiseSprite(player_texture,
                          "Data/Images/placeholder.png");
}

void Player::update(float dt)
{
  std::cout << direction.y << std::endl;
  getSprite()->move(direction.x * dt * speed, direction.y * dt * speed);
  getBoundingBox();
  checkJump();
}

void Player::move(sf::Event& event)
{
  if (event.key.code == sf::Keyboard::A)
    direction.x = -2;
  if (event.key.code == sf::Keyboard::D)
    direction.x = 2;
  if (on_ground)
  {
    if (event.key.code == sf::Keyboard::Space)
    {
      getSprite()->setPosition(top_l_x, top_l_y - 1);
      on_ground = false;
      is_jumping = true;
      direction.y = jump_power * -1;
    }
  }
}

void Player::checkJump()
{
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