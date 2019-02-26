#include <random>
#include <chrono>
#include <list>
#include <utility>
#include "player.h"

using std::list;
using std::pair;
using std::make_pair;


enum HitOrMiss
{
    MISS = 0,
    HIT  = 1,
    NONE = 2,
};


class COMplayer : public player
{
public:
	COMplayer();
    COMplayer(int x, int y);
    ~COMplayer() {};
	bool PlaceShip( std::vector<Ship>::iterator& _cship);
    bool FireShot(Board* _other_board);

private:
    // x and y could be difference sizes if implemented that why
    // (if someone was cruel and wanted to see the world burn)
    std::uniform_int_distribution<int> x_dist;
    std::uniform_int_distribution<int> y_dist;
    std::default_random_engine gen;

    int last_x, last_y;
    bool random_shot;
    vector<vector<HitOrMiss>> board_tracker;
    pair<int,int> last_shot;

};