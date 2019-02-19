#include "player.h"



player::player()
{

	_board =  new Board(55, 0, 50, 50, '~');
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
	validMove = false;
}

player::~player()
{
	delete _board;
}


bool player::PlaceShip( std::vector<Ship>::iterator& _cship, const shipcord& sp)
{
	// this is for the screen warning/user feedback
	bool warning;

    if (_cship != ships.end())
    {
        // this is ship placement 
        if (validMove && sp.place_ship)
        {
            _cship++;
        }
        else if (validMove)
        {
            _board->remove_ship(&(*_cship));
        }
        
        validMove = _board->place_ship(&(*_cship), sp.x, sp.y, sp.h_or_v);
        // this is the end of the ship placement 
        // warning if not a valid move
        warning = !validMove;
    }
    else
    {
        warning = false;
    }
    return warning;
}