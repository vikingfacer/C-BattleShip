#include "player.h"



player::player()
{
	_board =  new board(50, 50, '~');
	ships = std::vector<Ship>();
	ships.push_back(Ship('#', 10));
	ships.push_back(Ship('#', 8));
	ships.push_back(Ship('#', 8));
	ships.push_back(Ship('#', 5));
	ships.push_back(Ship('#', 5));
	ships.push_back(Ship('#', 5));
	ships.push_back(Ship('#', 2));
	ships.push_back(Ship('#', 2));
	ships.push_back(Ship('#', 2));
	ships.push_back(Ship('#', 2));
}

player::~player()
{
	delete _board;
}
