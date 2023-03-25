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
  getSprite()->move(direction.x * dt, direction.y * dt);
  checkJump();
}

void Player::move(sf::Event& event)
{
  if (event.key.code == sf::Keyboard::A)
    direction.x = -1 * speed;
  if (event.key.code == sf::Keyboard::D)
    direction.x = 1 * speed;
  if (on_ground)
  {
    if (event.key.code == sf::Keyboard::Space)
    {
      is_jumping = true;
      initial_y_pos = bot_l_y;
      getSprite()->move(0,-5);
      //std::cout << "Jump registered\n";
    }
  }
}

void Player::checkJump()
{
  if (collision.windowCheck(*this,window) == Collision::Type::BOTTOM && !is_jumping)
  {
    //std::cout << "collision detected\n";
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
  else
  {
    //std::cout << "On Ground\n";
  }
}

void Player::jumping()
{
  //std::cout << "Jumping\n";
  if ((bot_l_y + jump_height) < initial_y_pos)
  {
    is_jumping = false;
    direction.y = 10;
  }
  else
  {
    direction.y *= velocity;
    if (direction.y > 0)
      direction.y *= -1;
  }
}

void Player::falling()
{
  //std::cout << "Falling\n";
  direction.y *= velocity;
  if (direction.y > 350)
    direction.y = 350;
}

void Player::stop(sf::Event& event)
{
  if (event.key.code == sf::Keyboard::A && direction.x < 0)
    direction.x = 0;
  if (event.key.code == sf::Keyboard::D && direction.x > 0)
    direction.x = 0;
}