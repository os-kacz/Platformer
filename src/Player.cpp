#include "Player.h"

Player::Player(sf::RenderWindow& game_window) : window(game_window)
{
  speed *= speed_multiplier;
}

Player::~Player(){}

bool Player::initPlayer()
{
  direction.y = gravity;
  getSprite()->setScale(0.2,0.2);
  return initialiseSprite(player_texture,
                          "Data/Images/placeholder.png");
}

void Player::update(float dt)
{
  std::cout << direction.y << std::endl;
  getSprite()->move(direction.x * dt * speed, direction.y * dt * speed);
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
      is_jumping = true;
      direction.y = jump_power * -1;
    }
  }
}

void Player::checkJump()
{
  if (collision.windowCheck(*this,window) == Collision::Type::BOTTOM && !is_jumping)
  {
    on_ground = true;
    getSprite()->setPosition(getSprite()->getPosition().x, window.getSize().y - getSprite()->getGlobalBounds().height);
  }
  else
  {
    on_ground = false;
    getBoundingBox();
  }

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
  {
    is_jumping = false;
  }
  else
  {
    direction.y += velocity;
  }
}

void Player::falling()
{
  direction.y += velocity;
  if (direction.y > 4)
    direction.y = 4;
}

void Player::stop(sf::Event& event)
{
  if (event.key.code == sf::Keyboard::A && direction.x < 0)
    direction.x = 0;
  if (event.key.code == sf::Keyboard::D && direction.x > 0)
    direction.x = 0;
}