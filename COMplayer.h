#include <random>
#include <chrono>
#include <set>
#include <utility>
#include <algorithm>
#include "player.h"

using std::set;
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
    void stats();

    void drawLastHit();

private:

    pair<int, int> findNextHit(const pair<int,int>& _cpair, const pair<int,int>& _opp_pair);
    bool InRange(const pair<int, int>& _cpair);
    vector<pair<int, int>> discoverNotShot();
    vector<pair<int, int>> getCrossPeices(const pair<int, int>& );
    bool makeHit(Board* _other_board, const int& _x, const int& _y);
    bool fireRandShot(Board* _other_board);
    // x and y could be difference sizes if implemented that why
    // (if someone was cruel and wanted to see the world burn)
    // std::uniform_int_distribution<int>  pair_dist;
    std::default_random_engine gen;

    int last_x, last_y;
    bool random_shot;
    vector<vector<HitOrMiss>> board_tracker;
    pair<int,int> last_shot;

};

template<class T>
const pair<T, T> operator-(pair<T, T>lhs, pair<T, T>rhs)
{
    return pair<T,T>(lhs.first - rhs.first, lhs.second - rhs.second);
}
template<class T>
const pair<T, T> operator+(pair<T, T>lhs, pair<T, T>rhs)
{
    return pair<T,T>(lhs.first + rhs.first, lhs.second + rhs.second);
}

// bool(*)(const pair<int,int>& lhs, const pair<int,int>& rhs);