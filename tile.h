#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <chrono>

#include "drawable.h"
#include "Ship.h"

class Tile : public JDrawable
{
public:
  Tile() = delete;
  explicit Tile(const unsigned int &_x, unsigned const int &_y);
  Tile(const unsigned int &_x, const unsigned int &_y, const float &_size);

  friend std::ostream &operator<<(std::ostream &os, const Tile &t);
  void draw() const override;

  inline void set_x(const unsigned int &_x) { x = _x; };
  inline void set_y(const unsigned int &_y) { y = _y; };
  // inline void set_display(const char &_display) { display = _display; };
  inline void set_ship(Ship *_boat) { boat = _boat; };
  inline void set_is_shot(const bool &shot) { is_shot = shot; };
  inline void set_is_hit_mark(const bool &hit) { is_hit_mark = hit; };
  inline void set_is_mis_mark(const bool &mis) { is_mis_mark = mis; };

  Ship *get_ship() { return boat; };

  const unsigned int &get_x() { return x; };
  const unsigned int &get_y() { return y; };
  // const char get_display() { return (const char)display; };
  const bool get_is_shot() { return is_shot; };
  bool is_occupied() { return (boat != nullptr ? true : false); };

  ~Tile(){};

private:
  unsigned int x;
  unsigned int y;

  bool is_shot;
  bool is_hit_mark;
  bool is_mis_mark;
  // bool show_ship;
  float size;

  Ship *boat;
};

#endif