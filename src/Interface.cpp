#include "Interface.h"
Interface::Interface(sf::RenderWindow& game_window) : window(game_window)
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

  return true;
}