#include "Hazard.h"

Hazard::Hazard() {}

Hazard::~Hazard() {}

bool Hazard::initHazard()
{
  getSprite()->setScale(3,3);
  return initialiseSprite(
    texture,
    "Data/Images/kenney_pixelplatformer/Tiles/tile_0068.png");
}
void Hazard::update(GameObject& affector)
{

}
