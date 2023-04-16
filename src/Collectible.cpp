#include "Collectible.h"

Collectible::Collectible() {}

Collectible::~Collectible() {}

bool Collectible::initCollectible()
{
  getSprite()->setScale(3,3);
  return initialiseSprite(
    texture,
    "Data/Images/kenney_pixelplatformer/Tiles/tile_0067.png");
}
