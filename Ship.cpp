#include "Ship.h"
// #include "mediator.h"





Ship::Ship( const char& _display, const int& _length) :
  display(_display), length(_length)
{
	damage = 0;
}

Ship::~Ship() {}


