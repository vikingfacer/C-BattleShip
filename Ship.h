#ifndef SHIP_H
#define SHIP_H

#include <vector>

// #include "tile.h"
// #include "board.h"

enum orintation
{
    horizontal,
    vertical
};

class Ship
{
  public:
    Ship() = delete;
    explicit Ship(const char &display, const int &length);
    inline const unsigned int &get_length() { return length; };
    inline const unsigned int get_damage() { return damage; };
    inline char get_display() { return display; };
    inline void set_damage(const unsigned int &_damage) { damage = _damage; };
    inline unsigned int get_health() { return length - damage; };
    ~Ship();

  private:
    char display;
    unsigned int length;
    unsigned int damage;
};

#endif