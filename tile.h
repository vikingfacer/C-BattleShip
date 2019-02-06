#ifndef TILE_H
#define TILE_H

#include <iostream>

class tile
{
public:
	tile() = delete;
	explicit tile(const int& _x, const int& _y) : x(_x), y(_y), display('\0'), occupied(false) {};
	tile(const int& _x, const int& _y, const char& _display) : x(_x), y(_y), display(_display), occupied(false) {};
	inline friend std::ostream& operator<<(std::ostream& os, const tile& t) { os << " " << t.display << " "; return os;};
	void set_x(const int& _x) {x = _x;};
	void set_y(const int& _y) {y = _y;};
	void set_display(const int& _display) {display = _display;};
	void set_occupied(bool isit){occupied = isit;};
	const bool& is_occupied() { return occupied;};
	~tile() {};
private:
	int x;
	int y;
	char display;
	bool occupied;
};

#endif 