#ifndef PONGSFML_VECTOR_H
#define PONGSFML_VECTOR_H

class Vector
{
  public:
   float x;
   float y;
   float mag;
   float inverter;
   void normalise();
   void affector();
};

#endif // PONGSFML_VECTOR_H
