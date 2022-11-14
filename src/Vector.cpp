#include "Vector.h"
#include "Game.h"
#include <cmath>

void Vector::normalise()
{
  mag = sqrt(x*x + y*y);
  x = x/mag;
  y = y/mag;
}

void Vector::affector()
{
  x = x * mag;
  y = y * mag;
  x += (std::rand() % 2 + 1);
  y += (std::rand() % 2 + 1);
}