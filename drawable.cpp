#include "drawable.h"

void JDrawable::drawRectangle(const JShape &shape, const JColor &color) const
{
    DrawRectangle(shape.x, shape.y, shape.width, shape.height, color);
}


void JDrawable::drawRandPolygone(const JShape&shape, const JColor&color) const
{
	Vector2 point = { static_cast<int>(shape.x) + 5, static_cast<int>(shape.y) + 5};

    int rand_side = std::experimental::randint(5, 11);

    DrawPoly(point, rand_side, shape.width/2, 0, color); 

}