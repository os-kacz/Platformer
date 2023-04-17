#ifndef PLATFORMERSFML_INTERFACE_H
#define PLATFORMERSFML_INTERFACE_H

#import <iostream>
#import <SFML/Graphics.hpp>

class Interface
{
 public:
  Interface(sf::RenderWindow& game_window);
  virtual ~Interface();
  bool initText();
  sf::Text debug;
  sf::Text collisions;
  sf::Text jump_window;
  sf::Text main_text;
  sf::Text score;
  sf::Text lives;
 private:
  sf::RenderWindow& window;
  sf::Font font;
};

#endif // PLATFORMERSFML_INTERFACE_H
