#include "board.h"


board::board(const int& _rows, const int& _columns, char fill) :
rows(_rows), columns(_columns)
{
	plan = vector<vector<tile*>>();
	for (int i = 0; i < rows; i++)
	{
		vector<tile*> temp;
		for (int j = 0; j < columns; j++)
		{
			tile* temptile = new tile( j, i, fill);

			if (temptile)
			{
				temp.push_back(temptile);
			}
			else
			{
				cout << "new failed" << endl;
			}
		}
		plan.push_back(temp);
	}
}
board& board::operator=(const board& other)
{
	rows = other.rows;
	columns = other.columns;
	plan = other.plan;
	return *this;
}

board::board(const board& other_board) 
{
	// const char wave_display = other_board.get(0,0).get_display();
	plan = other_board.plan;
		
} // need to fix this 


board::~board()
{
	for(auto i : plan)
		for( auto j : i)
			delete j;
}

void board::draw()
{
	for(auto i : plan)
	{
		for( auto m : i)
		{
			m->draw();
		}
	}
}


bool board::place_ship(Ship* boat, const unsigned int& _x, const unsigned int& _y, orintation orin)
{
	// check if the ship can be moved there 
	// check if spaces has be defined 
	
	bool did_it_work = false;
	std::vector<tile*> placement;

	int boat_length = boat->get_length();
	if ( (_x + boat_length) < rows && (_y + boat_length) < columns )
	{
		if(orin == horizontal)
		{
			for (int i = _x; i < boat_length + _x; i++)
			{
				placement.push_back(plan[_x][i]);
			}
		}else
		if(orin == vertical)
		{
			for (int i = _y; i < boat_length + _y; i++)
			{
				placement.push_back(plan[i][_y]);
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
				did_it_work = true;
			}
		}
		if (did_it_work)
		{
			for (auto it : placement)
			{
				it->set_ship(boat);			
			}
		}
	}

	return did_it_work;
}

bool board::place_shot(board* other_board, const unsigned int& _x, const unsigned int& _y)
{
	tile* current_tile = other_board->plan[_x][_y];

	// check if a ship is there 
	// if a ship exists there then damage the ship 
	// then show on the tile that the ship is hit

	if (current_tile->is_occupied() && !current_tile->get_is_shot())
	{
		current_tile->get_ship()->set_damage(current_tile->get_ship()->get_damage() + 1);
		current_tile->set_is_shot(true);

		place_hit_marker(_x, _y);
		return true;
	}
	else
	{
		place_mis_marker(_x, _y);
		return false;
	}
}


// these two functions are helper functiosn to the place shot function they affect the other board

bool board::place_hit_marker(const unsigned int& _x, const unsigned int& _y)
{
	tile* current_tile = plan[_x][_y];

	if(!current_tile->get_is_shot())
	{
		current_tile->set_is_hit_mark(true);
		// current_tile->set_is_shot(true);
		return true;
	}

	return false;
}
bool board::place_mis_marker(const unsigned int& _x, const unsigned int& _y)
{
	tile* current_tile = plan[_x][_y];

	if(!current_tile->get_is_shot())
	{
		current_tile->set_is_mis_mark(true);
		// current_tile->set_is_shot(true);
		return true;
	}
	return false;
}
