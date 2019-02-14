#include "drawable.h"

void JDrawable::drawRectangle(const JShape &shape, const JColor &color) const
{
    DrawRectangle(shape.x, shape.y, shape.width, shape.height, color);
}