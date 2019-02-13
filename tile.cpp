#include "tile.h"


tile::tile(const unsigned int& _x,unsigned const int& _y, const char& _display) :tile( _x, _y, _display, '*', '0', '@', 10) {};

tile::tile(const unsigned int& _x, const unsigned int& _y, const char& _display, const char& _hit_mark, const char& _mis_mark, const char& _damage_mark, const float& _size) :
	x(_x), y(_y), display(_display), hit_mark(_hit_mark), mis_mark(_mis_mark), damage_mark(_damage_mark),
	is_shot(false), is_hit_mark(false), is_mis_mark(false), boat(nullptr), size(_size) {};


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

void tile::draw()
{
	// Rectangle tile = {x * 10, y * 10, 10, 10};
	// DrawRectangleRec(tile, BLUE);
// DrawRectangle(int posX, int posY, int width, int height, Color color);
	if (boat != nullptr)
	{
		DrawRectangle(x * 10, y * 10, 9, 9, BLACK);
	}else
	{
		DrawRectangle(x * 10, y * 10, 9, 9, BLUE);

	}
}