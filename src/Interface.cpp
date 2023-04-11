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
  debug.setCharacterSize(35);
  debug.setFillColor(sf::Color::White);
  debug.setPosition(0,0);

  collisions.setString("");
  collisions.setFont(font);
  collisions.setCharacterSize(35);
  collisions.setFillColor(sf::Color::White);
  collisions.setPosition(0,debug.getPosition().y + debug.getGlobalBounds().height);

  return true;
}