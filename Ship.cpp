#include "Ship.h"
// #include "mediator.h"





Ship::Ship(  const int& _length, const bool& _show) :
  length(_length), show(_show)
{
	damage = 0;
}

Ship::~Ship() {}


