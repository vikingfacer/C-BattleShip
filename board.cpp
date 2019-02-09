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
			cout << *m;
		}
		cout << endl;
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