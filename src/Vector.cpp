#include "Vector.h"
#include "Game.h"
#include <iostream>
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
    inverter = 1;
  }
  else
  {
    inverter = -1;
  }
  x += ((std::rand() % 3 + 1) * inverter);
  y += ((std::rand() % 3 + 1) * inverter);
}