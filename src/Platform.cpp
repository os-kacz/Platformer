#include "Platform.h"

Platform::Platform()
{

}

Platform::~Platform() {}

bool Platform::initPlatform()
{
  getSprite()->setScale(6,6);
  return initialiseSprite(texture, "Data/Images/kenney_pixelplatformer/Tiles/tile_0000.png");
}

void Platform::update()
{
  getBoundingBox();
}
