#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "Ship.h"
#include <raylib.h>
class tile
{
public:
	tile() =delete;
	explicit tile(const unsigned int& _x,unsigned const int& _y, const char& _display);
	tile(const unsigned int& _x, const unsigned int& _y, const char& _display, const char& _hit_mark, const char& _mis_mark, const char& _damage_mark, const float& _size);
	
	friend std::ostream& operator<<(std::ostream& os, const tile& t);
	void draw();


	inline void set_x(const unsigned int& _x) {x = _x;};
	inline void set_y(const unsigned int& _y) {y = _y;};
	inline void set_display(const char& _display) {display = _display;};
	inline void set_ship(Ship* _boat){boat = _boat;};
	inline void set_is_shot(const bool& shot){is_shot = shot;};
	inline void set_is_hit_mark(const bool& hit){is_hit_mark = hit;};
	inline void set_is_mis_mark(const bool& mis){is_mis_mark = mis;};


	Ship* get_ship(){return boat;};

	const unsigned int& get_x(){return x;};
	const unsigned int& get_y(){return y;};
	const char get_display(){return (const char) display;};
	bool get_is_shot(){return is_shot;};
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
	bool is_hit_mark;
	bool is_mis_mark;

	float size;

	Ship* boat;
};

#endif 