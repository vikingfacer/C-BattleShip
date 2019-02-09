#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "Ship.h"
class tile
{
public:
	tile() = delete;
	explicit tile(const unsigned int& _x,unsigned const int& _y) : x(_x), y(_y), display('\0'), boat(nullptr) {};
	tile(const unsigned int& _x, const unsigned int& _y, const char& _display) : x(_x), y(_y), display(_display), boat(nullptr) {};
	
	inline friend std::ostream& operator<<(std::ostream& os, const tile& t) { os << " " << (t.boat != nullptr ? t.boat->get_display() : t.display) << " "; return os;};
	
	void set_x(const unsigned int& _x) {x = _x;};
	void set_y(const unsigned int& _y) {y = _y;};
	void set_display(const char& _display) {display = _display;};
	void set_ship(Ship* _boat){boat = _boat;};
	
	const unsigned int& get_x(){return x;};
	const unsigned int& get_y(){return y;};
	bool is_occupied() { return (boat != nullptr ? true : false);};

	~tile() {};
private:
	unsigned int x;
	unsigned int y;
	char display;
	Ship* boat;
};

#endif 