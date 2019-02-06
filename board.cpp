#include "board.h"
#include "tile.h"

board::board(const int& _rows, const int& _columns) :
rows(_rows), columns(_columns)
{
	plan = vector<vector<tile*>>();
	for (int i = 0; i < rows; i++)
	{
		vector<tile*> temp;
		for (int j = 0; j < columns; j++)
		{
			tile* temptile = new tile( j, i, '0');
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