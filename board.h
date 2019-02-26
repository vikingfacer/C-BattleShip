#ifndef BOARD_H
#define BOARD_H


#include <vector>
#include <iostream>

#include "tile.h"
#include "Ship.h"

using std::vector;
using std::cout;
using std::endl;

class Board
{
public:
	Board() = delete;
	explicit Board(const float& _x, const float& _y, const int& _rows, const int& _columns, char fill);
	Board& operator=(const Board& other);
	Board(const Board& other_board);
	void draw();

	void remove_ship(Ship* _boat);
	bool place_ship(Ship* boat, const unsigned int& _x, const unsigned int& _y, orintation orin = horizontal);
	bool place_shot(Board* other_board, const unsigned int& _x, const unsigned int& _y);

	bool place_hit_marker(const unsigned int& _x, const unsigned int& _y);
	bool place_mis_marker(const unsigned int& _x, const unsigned int& _y);

	inline Tile* get(const unsigned int& _x, const unsigned int& _y) { return plan[_x][_y];}; // this needs to check bounds
	inline const int get_row(){return rows;};
	inline const int get_column(){return columns;};
	inline const int get_x(){return x;};
	inline const int get_y(){return y;};

	~Board();
private:
	vector<vector<Tile*>> plan;
	int rows, columns;
	float x,y;
};

#endif