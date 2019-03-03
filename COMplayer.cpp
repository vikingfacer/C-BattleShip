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

bool COMplayer::InRange(const pair<int, int>& _cpair)
{
    //  these are just separated for clarity
    bool condition1 = _cpair.first >= 0 && _cpair.second >= 0;
    bool condition2 = _cpair.first < board_tracker.size() && _cpair.second < board_tracker[0].size();

    return condition1 && condition2;
}

pair<int, int> COMplayer::findNextHit(const pair<int,int>& _cpair, const pair<int,int>& _opp_pair)
{
    pair<int,int> foundpair(_opp_pair);

    // we only should need to search up
    if (_cpair.first == _opp_pair.first)
    {
        for(int i = _opp_pair.second; i < board_tracker.size(); i++)
        {
            if (board_tracker[_opp_pair.first][i] == NONE)
            {
                foundpair.first = _opp_pair.first;
                foundpair.second= i;
                break;
            }
        }
    }
    else
    if(_cpair.second == _opp_pair.second)
    {
        for(int i = _opp_pair.first; i < board_tracker[0].size(); i++)
        {
            if (board_tracker[i][_opp_pair.second] == NONE)
            {
                foundpair.first = i;
                foundpair.second= _opp_pair.second;
                break;
            }
        }
    }
    return foundpair;
}


bool COMplayer::FireShot(Board* _other_board)
{
    bool did_we_fire = false;
    if (random_shot)
    {
        random_shot = !fireRandShot(_other_board);
    }
    else
    {
        cout << "this is not a random shot" << endl;

        vector<pair<int,int>> cross_peices = getCrossPeices(last_shot);

        // if there are no NONE tiles or Hit tiles to discover then do a random shot and return
        if (cross_peices.size() == 0)
        {
            random_shot = !fireRandShot(_other_board);
            return true;
        }
        else
        {
            for(auto t : cross_peices)
            {
                cout << "x: " << t.first << " y: " << t.second << endl;
            }

            for(auto t : cross_peices)
            {
                if (board_tracker[t.first][t.second] == HitOrMiss::HIT)
                {
                    // need to find the opposite tile from the hit tile
                    auto  opposite_tile = last_shot + (last_shot - t);

                        // these two cases should either mark the end of
                    if(InRange(opposite_tile) && board_tracker[opposite_tile.first][opposite_tile.second] == HitOrMiss::HIT)
                    {
                            cout << "line: " << __LINE__ << endl;

                        auto nhit = findNextHit(last_shot, opposite_tile);
                        if(board_tracker[nhit.first][nhit.second] != HitOrMiss::MISS && makeHit(_other_board, nhit.first, nhit.second))
                        {
                            cout << "line: " << __LINE__ << endl;
                            random_shot = false;
                            return true;
                        }
                        else
                        {
                            random_shot = true;
                        }
                        break;
                    }
                    else
                    if (InRange(opposite_tile) && board_tracker[opposite_tile.first][opposite_tile.second] == HitOrMiss::NONE)
                    {
                            cout << "line: " << __LINE__ << endl;
                        if(makeHit(_other_board, opposite_tile.first, opposite_tile.second))
                        {
                            cout << "line: " << __LINE__ << endl;
                            random_shot = false;
                            return true;
                        }
                        break;
                    }
                    else
                    // i need to manage the case for if the opposite is nothing
                    if(InRange(opposite_tile) && board_tracker[opposite_tile.first][opposite_tile.second] == HitOrMiss::MISS)
                        // && board_tracker[last_shot.first][last_shot.second] != HitOrMiss::MISS)
                    { // trying t last shot might work better
                            cout << "line: " << __LINE__ << endl;

                        auto nhit = findNextHit(last_shot, opposite_tile);
                        if(board_tracker[nhit.first][nhit.second] != HitOrMiss::MISS && makeHit(_other_board, nhit.first, nhit.second))
                        {
                            cout << "line: " << __LINE__ << endl;

                            random_shot = false;
                            return true;
                        }
                        else
                        {
                            random_shot = true;
                        }
                        break;
                    }

                }
                else
                {
                   if(makeHit(_other_board, t.first, t.second))
                   {
                            cout << "line: " << __LINE__ << endl;
                        last_shot = t;
                        random_shot = false;
                        return true;
                   }
                   break;
                }
            }
        }
        random_shot = false;
    }
    return false;
}

void COMplayer::stats()
{
    int misses = 0, hits = 0, nothings = 0, total_tiles = board_tracker.size() * board_tracker[0].size();

    for(auto t : board_tracker)
        for (auto element: t)
        {
            if (element == HitOrMiss::HIT)
            {
                hits++;
            }
            else
            if (element == HitOrMiss::MISS)
            {
                misses++;
            }
            else
            {
                nothings++;
            }
        }

    cout << "\nlast shot: x: " <<last_shot.first << " y: " << last_shot.second << endl;
    cout << "misses: " << misses <<" " << (float)misses/(float)total_tiles * 100 << "%" << endl;
    cout << "hits: " << hits << " " << (float)hits/(float)total_tiles * 100 << "%" << endl;
    cout << "totals: " << total_tiles  << " game left " << (1.0 - (float)nothings/(float)total_tiles)  * 100 <<"%" << endl;
}

void COMplayer::drawLastHit()
{

    Vector2 point = { static_cast<int>(last_shot.first)*10 + 5 + _board.get_x(), static_cast<int>(last_shot.second)*10 + 5 + _board.get_y()};

    DrawPoly(point, 6, 4, 0, PINK);

}

