#include "player.h"



player::player() : player(55,0){}


player::player(const int& x, const int& y, const bool& show_ships) : _board(Board(x, y, 50, 50)), ships(std::vector<Ship>()), validMove(false)
{
    ships.push_back(Ship( 10, show_ships));
    ships.push_back(Ship( 8, show_ships));
    ships.push_back(Ship( 8, show_ships));
    ships.push_back(Ship( 5, show_ships));
    ships.push_back(Ship( 5, show_ships));
    ships.push_back(Ship( 5, show_ships));
    ships.push_back(Ship( 2, show_ships));
    ships.push_back(Ship( 2, show_ships));
    ships.push_back(Ship( 2, show_ships));
    ships.push_back(Ship( 2, show_ships));
}




player::~player()
{}


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
            _board.remove_ship(&(*_cship));
        }

        validMove = _board.place_ship(&(*_cship), sp.x, sp.y, sp.h_or_v);
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

int player::getHealth()
{
	int health = 0;
	for( auto boat : ships)
	{
		health += boat.get_health();
	}
	return health;
}