#ifndef TILE_H
#define TILE_H

#include <iostream>

class tile
{
public:
	tile() = delete;
	explicit tile(const unsigned int& _x,unsigned const int& _y) : x(_x), y(_y), display('\0'), occupied(false) {};
	tile(const unsigned int& _x, const unsigned int& _y, const char& _display) : x(_x), y(_y), display(_display), occupied(false) {};
	inline friend std::ostream& operator<<(std::ostream& os, const tile& t) { os << " " << t.display << " "; return os;};
	void set_x(const unsigned int& _x) {x = _x;};
	void set_y(const unsigned int& _y) {y = _y;};
	const unsigned int& get_x(){return x;};
	const unsigned int& get_y(){return y;};
	void set_display(const char& _display) {display = _display;};
	void set_occupied(bool isit){occupied = isit;};
	const bool& is_occupied() { return occupied;};
	~tile() {};
private:
	unsigned int x;
	unsigned int y;
	char display;
	bool occupied;
};

#endif 