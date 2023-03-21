#ifndef PLATFORMERSFML_VECTOR_H
#define PLATFORMERSFML_VECTOR_H

struct Vector
{
  Vector(float x_, float y_);
  Vector(const Vector& rhs);

  void normalise();

  float x = 0;
  float y = 0;
};

#endif // PLATFORMERSFML_VECTOR_H
