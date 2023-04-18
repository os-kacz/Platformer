#include "Player.h"

Player::Player(sf::RenderWindow& game_window) : window(game_window)
{
  srand(time(nullptr));
  speed *= speed_multiplier;
}

Player::~Player(){}

bool Player::initPlayer()
{
  if (!jump_buffer[0].loadFromFile("Data/SFX/jump.wav"))
  {
    std::cout << "could not load jump_sfx sound\n";
    return false;
  }
  if (!jump_buffer[1].loadFromFile("Data/SFX/jump_alt.wav"))
  {
    std::cout << "could not load jump_sfx sound\n";
    return false;
  }
  if (!walk_buffer[0].loadFromFile("Data/SFX/walk.wav"))
  {
    std::cout << "could not load walk_sfx sound\n";
    return false;
  }
  if (!walk_buffer[1].loadFromFile("Data/SFX/walk_alt.wav"))
  {
    std::cout << "could not load walk_sfx sound\n";
    return false;
  }
  if (!gem_buffer.loadFromFile("Data/SFX/pickupCoin.wav"))
  {
    std::cout << "could not load pickupCoin sound\n";
    return false;
  }
  if (!hurt_buffer.loadFromFile("Data/SFX/hitHurt.wav"))
  {
    std::cout << "could not load hurt sound\n";
    return false;
  }
  jump_sfx_1.setBuffer(jump_buffer[0]);
  jump_sfx_2.setBuffer(jump_buffer[1]);
  walk_sfx_1.setBuffer(walk_buffer[0]);
  walk_sfx_2.setBuffer(walk_buffer[1]);
  gem_sfx.setBuffer(gem_buffer);
  hurt_sfx.setBuffer(hurt_buffer);
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
      int rdm_jump_sound = std::rand() % 2 + 1;
      if (rdm_jump_sound == 1)
        jump_sfx_1.play();
      else
        jump_sfx_2.play();
    }
  }
}
void Player::playCollideSFX(Collision::Type collision)
{
  if (!played && direction.x != 0 && sound_window.getElapsedTime().asSeconds() > 0.2)
  {
    sound_window.restart();
    int rdm_walk_sound = std::rand() % 2 + 1;
    if (rdm_walk_sound == 1)
      walk_sfx_1.play();
    else
      walk_sfx_2.play();
    played = true;
  }
  if (collision != Collision::Type::NONE)
    played = false;
}

void Player::playGemSFX()
{
  gem_sfx.play();
}

void Player::playHurtSFX()
{
  hurt_sfx.play();
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

void Player::stop(sf::Event& event)
{
  if (event.key.code == sf::Keyboard::A && direction.x < 0)
    direction.x = 0;
  if (event.key.code == sf::Keyboard::D && direction.x > 0)
    direction.x = 0;
}
