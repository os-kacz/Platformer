#ifndef PLATFORMERSFML_PLATFORM_H
#define PLATFORMERSFML_PLATFORM_H

#include "GameObject.h"

class Platform : public GameObject
{
 public:
  Platform();
  ~Platform();
  bool initPlatform();
  bool walkable = true;
 private:
  sf::Texture texture;
};

#endif // PLATFORMERSFML_PLATFORM_H
