#ifndef PLAYER_H
#define PLAYER_H



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
    player(int x, int y);
	~player();
	// void place_ships();
	bool virtual PlaceShip( std::vector<Ship>::iterator& _cship, const shipcord& sp);
	int getHealth();
	vector<Ship> ships;
	Board  _board;
	bool validMove;

};

#endif