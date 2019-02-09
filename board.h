#ifndef BOARD_H
#define BOARD_H 


#include <vector>
#include <iostream>

#include "tile.h"
#include "Ship.h"

using std::vector;
using std::cout;
using std::endl;

class board
{
public:
	board() = delete;
	explicit board( const int& _rows, const int& _columns, char fill);
	void draw();

	bool place_ship(Ship* boat, const unsigned int& _x, const unsigned int& _y, orintation orin = horizontal);
	bool place_shot(const unsigned int& _x, const unsigned int& _y);
	bool place_hit_marker(const unsigned int& _x, const unsigned int& _y);
	bool place_mis_marker(const unsigned int& _x, const unsigned int& _y);
	
	inline tile* get(const unsigned int& _x, const unsigned int& _y) { return plan[_x][_y];};
	inline const int& get_row(){return rows;};
	inline const int& get_column(){return columns;};
	~board();
private:
	vector<vector<tile*>> plan;
	int rows, columns;
};

#endif