#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "raylib.h"

#include <utility>

using JColor = Color;

struct JShape
{
  unsigned int x;
  unsigned int y;
  unsigned int width;
  unsigned int height;
};

using JShape = struct JShape;

// Drawable interface
class JDrawable
{
public:
  JDrawable()
  {
  }

  ~JDrawable() = default;

  virtual void draw() const = 0;

protected:
  virtual void drawRectangle(const JShape &, const JColor &) const;
};

#endif // DRAWABLE_H
