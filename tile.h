#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "Ship.h"
class tile
{
public:
	tile() = delete;
	explicit tile(const unsigned int& _x,unsigned const int& _y) :
		x(_x), y(_y), display('\0'), hit_mark('@'), mis_mark('0'), damage_mark('*'), is_shot(false), boat(nullptr) {};

	tile(const unsigned int& _x, const unsigned int& _y, const char& _display) :
		x(_x), y(_y), display(_display), hit_mark('@'), mis_mark('0'), damage_mark('*'), is_shot(false), boat(nullptr) {};
	
	inline friend std::ostream& operator<<(std::ostream& os, const tile& t) { 
		os << " " << 
			(t.boat != nullptr ? 
				(t.is_shot? t.hit_mark : t.boat->get_display()) : t.display) 
			<< " "; return os;};
	
	inline void set_x(const unsigned int& _x) {x = _x;};
	inline void set_y(const unsigned int& _y) {y = _y;};
	inline void set_display(const char& _display) {display = _display;};
	inline void set_ship(Ship* _boat){boat = _boat;};
	inline void set_is_shot(const bool& shot){is_shot = shot;};

	const unsigned int& get_x(){return x;};
	const unsigned int& get_y(){return y;};
	bool get_is_shot(){return is_shot;};
	Ship* get_ship(){return boat;};
	bool is_occupied() { return (boat != nullptr ? true : false);};

	~tile() {};
private:
	unsigned int x;
	unsigned int y;
	char display;
	char hit_mark; // need to add to constructors and ostream 
	char mis_mark;
	char damage_mark;
	bool is_shot;
	Ship* boat;
};

#endif 