#include "Interface.h"
Interface::Interface(sf::RenderWindow& game_window, Camera& camera) : window(game_window), camera(camera)
{

}

Interface::~Interface() {}

bool Interface::initText()
{
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Could not load font\n";
    return false;
  }
  debug.setString("");
  debug.setFont(font);
  debug.setCharacterSize(25);
  debug.setFillColor(sf::Color::White);
  debug.setPosition(0,0);

  collisions.setString("");
  collisions.setFont(font);
  collisions.setCharacterSize(25);
  collisions.setFillColor(sf::Color::White);
  collisions.setPosition(0,debug.getPosition().y + debug.getGlobalBounds().height);

  jump_window.setString("");
  jump_window.setFont(font);
  jump_window.setCharacterSize(25);
  jump_window.setFillColor(sf::Color::White);
  jump_window.setPosition(0,collisions.getPosition().y + collisions.getGlobalBounds().height);

  main_text.setString("Press Enter to play the Platformer\n\n- 'A' & 'D' to move sideways\n- 'Space' to jump\n- Move into walls to grip them\n- Collect the gems, avoid pits and spikes!");
  main_text.setFont(font);
  main_text.setCharacterSize(45);
  main_text.setFillColor(sf::Color::White);
  main_text.setPosition(
    camera.getCamera()->getCenter().x - (main_text.getGlobalBounds().width / 2),
    camera.getCamera()->getCenter().y - (main_text.getGlobalBounds().height / 2));

  score.setString("Score: 0");
  score.setFont(font);
  score.setCharacterSize(35);
  score.setFillColor(sf::Color::White);
  score.setPosition(camera.getCamera()->getCenter().x - score.getGlobalBounds().width,0);

  lives.setString("Lives: 4");
  lives.setFont(font);
  lives.setCharacterSize(35);
  lives.setFillColor(sf::Color::White);
  lives.setPosition(camera.getCamera()->getCenter().x - score.getGlobalBounds().width,50);

  return true;
}
void Interface::textInView()
{
  lives.setPosition(
    camera.getCamera()->getCenter().x - (camera.getCamera()->getSize().x / 2) + 10,
    camera.getCamera()->getCenter().y - (camera.getCamera()->getSize().y / 2));
  score.setPosition(
    camera.getCamera()->getCenter().x - (camera.getCamera()->getSize().x / 2) + 10,
    camera.getCamera()->getCenter().y - (camera.getCamera()->getSize().y / 2) + 50);
  main_text.setPosition(
    camera.getCamera()->getCenter().x - (main_text.getGlobalBounds().width / 2),
    camera.getCamera()->getCenter().y - (main_text.getGlobalBounds().height / 2));
}
