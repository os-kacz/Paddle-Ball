#include "Vector.h"
#include "Game.h"
#include <iostream>
#include <cmath>

void Vector::normalise()
{
  float mag = sqrt(x*x + y*y);
  x = x/mag;
  y = y/mag;
}