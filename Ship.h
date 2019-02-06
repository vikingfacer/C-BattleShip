#ifndef SHIP_H
#define SHIP_H

#include <vector>

#include "tile.h"
#include "board.h"

enum orintation {
	horizontal,
	vertical
};

class Ship
{
public:
	Ship() =delete;
	explicit Ship( const char& display, const int& length);
	bool move( board& _board, const unsigned int& _x, const unsigned int& _y, orintation orin = horizontal);

	~Ship();
private:
	std::vector<tile*> spaces;
	char display;
	int length;
	int damage;
};

#endif