
#include "Ship.h"
#include "board.h"
#include <vector>

using std::vector;

class player
{
public:
	player();
	~player();
	// void place_ships();

	vector<Ship> ships;
	Board*  _board;

};