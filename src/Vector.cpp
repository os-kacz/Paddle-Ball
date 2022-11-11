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
  float variation_degree = std::rand() % 2 + 1;
  if (variation_degree == 1)
  {
    x += ((std::rand() % 10 + 1) * 1);
    y += ((std::rand() % 10 + 1) * 1);
  }
  else
  {
    x += ((std::rand() % 10 + 1) * -1);
    y += ((std::rand() % 10 + 1) * -1);
  }
}