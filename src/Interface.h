#ifndef PLATFORMERSFML_INTERFACE_H
#define PLATFORMERSFML_INTERFACE_H

#import <iostream>
#import <SFML/Graphics.hpp>
#import "Camera.h"

class Interface
{
 public:
  Interface(sf::RenderWindow& game_window, Camera& camera);
  virtual ~Interface();
  bool initText();
  void textInView();
  sf::Text main_text;
  sf::Text score;
  sf::Text lives;
 private:
  sf::RenderWindow& window;
  sf::Font font;
  Camera& camera;
};

#endif // PLATFORMERSFML_INTERFACE_H
