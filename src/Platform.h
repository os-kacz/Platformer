#ifndef PLATFORMERSFML_PLATFORM_H
#define PLATFORMERSFML_PLATFORM_H

#include "GameObject.h"

class Platform : public GameObject
{
  Platform();
  ~Platform();
  bool initPlatform();
};

#endif // PLATFORMERSFML_PLATFORM_H
