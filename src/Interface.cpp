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

  main_text.setString("Press Enter to play the Platformer\n\n- 'A' & 'D' to move sideways\n- 'Space' to jump"
                      "\n- Move into walls to grip them\n- Collect the gems, avoid pits and spikes!"
                      "\n\nPress '1', '2', or '3' to switch levels");
  main_text.setFont(font);
  main_text.setCharacterSize(35);
  main_text.setFillColor(sf::Color::White);

  score.setString("Score: 0");
  score.setFont(font);
  score.setCharacterSize(25);
  score.setFillColor(sf::Color::White);

  lives.setString("Lives: 4");
  lives.setFont(font);
  lives.setCharacterSize(25);
  lives.setFillColor(sf::Color::White);

  return true;
}
void Interface::textInView()
{
  lives.setPosition(
    camera.getCamera()->getCenter().x - (camera.getCamera()->getSize().x / 2) + 10,
    camera.getCamera()->getCenter().y - (camera.getCamera()->getSize().y / 2));
  score.setPosition(
    camera.getCamera()->getCenter().x - (camera.getCamera()->getSize().x / 2) + 10,
    camera.getCamera()->getCenter().y - (camera.getCamera()->getSize().y / 2) + 30);
  main_text.setPosition(
    camera.getCamera()->getCenter().x - (main_text.getGlobalBounds().width / 2),
    camera.getCamera()->getCenter().y - (main_text.getGlobalBounds().height / 0.9));
}
