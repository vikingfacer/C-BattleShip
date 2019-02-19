
#include "Ship.h"
#include "board.h"
#include <vector>

using std::vector;

// this should be in the player input class
struct shipcord
{
    int x, y;
    orintation h_or_v;
    bool place_ship;
};

class player
{
public:
	player();
	~player();
	// void place_ships();
	bool PlaceShip( std::vector<Ship>::iterator& _cship, const shipcord& sp);

	vector<Ship> ships;
	Board*  _board;
	bool validMove;

};