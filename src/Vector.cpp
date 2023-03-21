#include "Vector.h"
#include <math.h>

Vector::Vector(float x_, float y_) : x(x_), y(y_) {}

Vector::Vector(const Vector& rhs)
{
  this->x = rhs.x;
  this->y = rhs.y;
}

void Vector::normalise()
{
  float magnitude = sqrtf((x * x) + (y * y));

  if (!magnitude)
    return;

  x /= magnitude;
  y /= magnitude;
}