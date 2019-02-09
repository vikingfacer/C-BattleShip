#include "tile.h"
	unsigned int x;
	unsigned int y;
	char display;
	char hit_mark; // need to add to constructors and ostream 
	char mis_mark;
	char damage_mark;
	
	bool is_shot;
	bool is_hit_mark;
	bool is_mis_mark;

	Ship* boat;


tile::tile(const unsigned int& _x,unsigned const int& _y, const char& _display) :tile( _x, _y, _display, '*', '0', '@') {};

tile::tile(const unsigned int& _x, const unsigned int& _y, const char& _display, const char& _hit_mark, const char& _mis_mark, const char& _damage_mark) :
	x(_x), y(_y), display(_display), hit_mark(_hit_mark), mis_mark(_mis_mark), damage_mark(_damage_mark),
	is_shot(false), is_hit_mark(false), is_mis_mark(false), boat(nullptr) {};


std::ostream& operator<<(std::ostream& os, const tile& t) { 

	char char_display = t.display;
	if(t.boat != nullptr)
	{
		if (t.is_shot)
		{
			char_display = t.damage_mark;
		}else
		{
			char_display = t.boat->get_display();
		}
	}
	else
	{
		if(t.is_mis_mark)
		{
			char_display = t.mis_mark;
		}
		else if(t.is_hit_mark)
		{
			char_display = t.hit_mark;
		}
	}
	os << " " << char_display << " "; return os;};