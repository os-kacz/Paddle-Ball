#include "Vector.h"
#include <cmath>

void Vector::normalise()
{
  mag = sqrt(x*x + y*y);
  x = x/mag;
  y = y/mag;
}