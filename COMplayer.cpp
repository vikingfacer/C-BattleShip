#include "COMplayer.h"



COMplayer::COMplayer() :
    gen(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())),
    board_tracker(vector<vector<HitOrMiss>>(_board.get_row(), vector<HitOrMiss>(_board.get_column(), HitOrMiss::NONE))),
    random_shot(true),
    last_shot(pair<int,int>())
{};


COMplayer::COMplayer(int x, int y) : player( x, y),
    gen(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())),
    board_tracker(vector<vector<HitOrMiss>>(_board.get_row(), vector<HitOrMiss>(_board.get_column(), HitOrMiss::NONE))),
    random_shot(true),
    last_shot(pair<int,int>())
{};


bool COMplayer::PlaceShip( std::vector<Ship>::iterator& _cship)
{

    std::uniform_int_distribution<int> x_dist(0, _board.get_row()- 1);
    std::uniform_int_distribution<int> y_dist(0, _board.get_column() -1);

    bool warning;

    if (_cship != ships.end())
    {
        int gen_x = x_dist(gen);
        int gen_y = y_dist(gen);

        orintation h_or_v = ((bool) gen_y & gen_x & 1)? horizontal : vertical;

        // this is ship placement
        if (validMove)
        {
            _cship++;
        }
        validMove = _board.place_ship(&(*_cship), gen_x, gen_y, h_or_v);

        // this is the end of the ship placement
        // warning if not a valid move
        warning = !validMove;
    }
    else
    {
        warning = false;
    }
    return warning;
};

vector<pair<int, int>> COMplayer::discoverNotShot()
{
    std::vector<pair<int, int>> NotShot;
    for(int i = 0; i < board_tracker.size(); i++)
    {
        for(int j = 0; j < board_tracker[0].size(); j++)
        {
            if (board_tracker[i][j] == HitOrMiss::NONE)
            {
                NotShot.push_back(pair<int,int>(i,j));
            }
        }
    }
    return NotShot;
}

// this function only returns the None or Hit tiles
vector<pair<int, int>> COMplayer::getCrossPeices(const pair<int,int>& _last_shot)
{
    std::vector<pair<int,int>> cross;

    if (_last_shot.first > 0 && board_tracker[_last_shot.first-1][_last_shot.second] != HitOrMiss::MISS)
    {
        cross.push_back(pair<int,int>(_last_shot.first -1, _last_shot.second));
    }
    if (_last_shot.first < (_board.get_row() - 1) && board_tracker[_last_shot.first+1][_last_shot.second] != HitOrMiss::MISS)
    {
        cross.push_back(pair<int,int>(_last_shot.first +1, _last_shot.second));
    }

    // * Y axis*
    if (_last_shot.second > 0 && board_tracker[_last_shot.first][_last_shot.second-1] != HitOrMiss::MISS)
    {
        cross.push_back(pair<int,int>(_last_shot.first, _last_shot.second -1));
    }
    if (_last_shot.second < (_board.get_column() - 1) && board_tracker[_last_shot.first][_last_shot.second+1] != HitOrMiss::MISS)
    {
        cross.push_back(pair<int,int>(_last_shot.first, _last_shot.second +1));
    }

    for(auto t: cross)
    {
        cout << "x: " << t.first << ", y: " << t.second << std::flush;
    }
    cout << endl;

    return cross;
}


bool COMplayer::fireRandShot(Board* _other_board)
{
    bool hit = false;
    auto tiles_not_shot = discoverNotShot();
    std::uniform_int_distribution<int> pair_dist(0, tiles_not_shot.size());
    int gen_pair = pair_dist(gen);
    int new_x = tiles_not_shot[gen_pair].first;
    int new_y = tiles_not_shot[gen_pair].second;


    hit = makeHit(_other_board, new_x,new_y);

    return hit;

}

// this function only returns if the hit was a hit
bool COMplayer::makeHit(Board* _other_board, const int& _x, const int& _y)
{
    bool hit = false;
    if (_board.place_shot(_other_board, _x, _y))
    {
        hit = true;
        last_shot.first = _x;
        last_shot.second= _y;
        board_tracker[_x][_y] = HitOrMiss::HIT;
    }
    else
    {
        board_tracker[_x][_y] = HitOrMiss::MISS;
    }
    return hit;
}



bool COMplayer::FireShot(Board* _other_board)
{
    bool did_we_fire = false;
    if (random_shot)
    {
        random_shot = !fireRandShot(_other_board);
        // random_shot = true;
    }
    else
    {
        cout << "this is not a random shot" << endl;

        vector<pair<int,int>> cross_peices = getCrossPeices(last_shot);

        // if there are no NONE tiles or Hit tiles to discover then do a random shot and return
        if (cross_peices.size() == 0)
        {
            random_shot = true;
            did_we_fire = false;
        }
        else
        {
            //// for finding the next shot there are 3/4 options per ordination

            //// if we find a tile that has not been hit we hit that
            for(auto t : cross_peices)
            {
                if (board_tracker[t.first][t.second] == HitOrMiss::NONE)
                {
                   random_shot = !makeHit(_other_board, t.first, t.second);
                   // return true;
                }
            }

            // for(auto t : cross_peices)
            // {
            //     if (board_tracker[t.first][t.second] == HitOrMiss::Hit)
            //     {
            //         // need to find the opposite tile from the hit tile
            //         int new_x = last_shot.first - (last_shot.first - t.first);
            //         int new_y = - (last_shot.second - t.second);

            //         if (last_shot.fist - difference_x < 0 || last_shot.second - difference_y < 0 || )
            //         {
            //             random_shot = true;
            //             return false;
            //         }

            //         makeHit(_other_board, t.first, t.second);
            //     }
            // }

        }
        random_shot = true;
    }
    return false;
}

