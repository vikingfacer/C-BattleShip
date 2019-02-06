#include "Ship.h"

Ship::Ship( const char& _display, const int& _length) :
 display(_display), length(_length)
{
	spaces = std::vector<tile*>();
	spaces.reserve(length);
	damage = 0;
}

Ship::~Ship() {}


bool Ship::move(board& _board, const unsigned int& _x, const unsigned int& _y, orintation orin)
{
	// check if the ship can be moved there 
	// check if spaces has be defined 
	
	bool did_it_work = false;
	std::vector<tile*> placement;


	if ( (_x + length) < _board.get_row() && (_y + length) < _board.get_column() )
	{
		if(orin == horizontal)
		{
			for (int i = _x; i < length; i++)
			{
				placement.push_back(_board.get(_y, i));
			}
		}else
		{
			for (int i = _y; i < length; i++)
			{
				placement.push_back(_board.get( i, _x));
			}
		}

		for(auto t : placement)
		{
			if (t->is_occupied())
			{
				did_it_work = false;
				break;
			}
			else
			{
				t->set_occupied(true);
				t->set_display(display);
				did_it_work = true;
			}
		}
	}


	return did_it_work;
}
