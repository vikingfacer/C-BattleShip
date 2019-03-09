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
    explicit Ship(const int &length, const bool& _show  = true);
    inline const unsigned int &get_length() { return length; };
    inline const unsigned int get_damage() { return damage; };
    inline const bool is_show(){return show; };
    inline void set_show(const bool& _show){show = _show;};
    inline void set_damage(const unsigned int &_damage) { damage = _damage;};
    inline unsigned int get_health() { return length - damage; };
    ~Ship();

  private:
  	bool show;

    unsigned int length;
    unsigned int damage;
};

#endif