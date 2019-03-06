#include "COMplayer.h"



COMplayer::COMplayer() :
    gen(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())),
    board_tracker(vector<vector<HitOrMiss>>(_board.get_row(), vector<HitOrMiss>(_board.get_column(), HitOrMiss::NONE))),
    random_shot(true),
    last_shots(vector<pair<int,int>>()),
    last_shot(pair<int,int>()),
    first(true)
{};


COMplayer::COMplayer(int x, int y) : player( x, y),
    gen(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())),
    board_tracker(vector<vector<HitOrMiss>>(_board.get_row(), vector<HitOrMiss>(_board.get_column(), HitOrMiss::NONE))),
    random_shot(true),
    last_shots(vector<pair<int,int>>()),
    last_shot(pair<int,int>()),
    first(true)

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
    auto tiles_not_shot = discoverNotShot();
    std::uniform_int_distribution<int> pair_dist(0, tiles_not_shot.size());
    int gen_pair = pair_dist(gen);
    int new_x = tiles_not_shot[gen_pair].first;
    int new_y = tiles_not_shot[gen_pair].second;

    if (first)
    {
        new_x = 5;
        new_y = 5;
    }

    return makeHit(_other_board, new_x,new_y);
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
        last_shots.push_back(last_shot);
    }
    else
    {
        board_tracker[_x][_y] = HitOrMiss::MISS;
    }
    return hit;
}

bool COMplayer::makeHit(Board* _other_board, const pair<int,int>& _pair)
{
    return makeHit(_other_board, _pair.first, _pair.second);
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
    pair<int,int> foundpair(_cpair);

    // we only should need to search up
    if (_cpair.first == _opp_pair.first)
    {
        if (_opp_pair.second - _cpair.second > 0 )
        {
            for(int i = _cpair.second; i > 0; i--)
            {
                if (board_tracker[_cpair.first][i] == NONE)
                {
                    foundpair.first = _cpair.first;
                    foundpair.second= i;
                    break;
                }
                else
                if (board_tracker[_cpair.first][i] == MISS)
                {
                    break;
                }
            }
        }
        else
        {
            for(int i = _cpair.second; i < board_tracker.size(); i++)
            {
                if (board_tracker[_cpair.first][i] == NONE)
                {
                    foundpair.first = _cpair.first;
                    foundpair.second= i;
                    break;
                }
                else
                if (board_tracker[_cpair.first][i] == MISS)
                {
                    break;
                }
            }
        }
    }
    else
    if(_cpair.second == _opp_pair.second)
    {
        if (_opp_pair.first - _cpair.first > 0)
        {
            for(int i = _cpair.first; i > 0; i--)
            {
                if (board_tracker[i][_cpair.second] == NONE)
                {
                    foundpair.first = i;
                    foundpair.second= _cpair.second;
                    break;
                }
                if (board_tracker[i][_cpair.second] == MISS)
                {
                    break;
                }
            }
        }
        else
        {
            for(int i = _opp_pair.first; i < board_tracker[0].size(); i++)
            {
                if (board_tracker[i][_opp_pair.second] == NONE)
                {
                    foundpair.first = i;
                    foundpair.second= _opp_pair.second;
                    break;
                }
                if (board_tracker[i][_cpair.second] == MISS)
                {
                    break;
                }
            }
        }
    }
    return foundpair;
}

pair<int, int> COMplayer::findNextMiss(const pair<int,int>& _cpair, const pair<int,int>& _opp_pair)
{
    pair<int,int> foundpair(_cpair);

    // we only should need to search up
    if (_cpair.first == _opp_pair.first)
    {
        if (_opp_pair.second - _cpair.second > 0 )
        {
            for(int i = _cpair.second; i > 0; i--)
            {
                if (board_tracker[_cpair.first][i] == MISS)
                {
                    foundpair.first = _cpair.first;
                    foundpair.second= i;
                    break;
                }
                else
                if (board_tracker[_cpair.first][i] == NONE)
                {
                    break;
                }
            }
        }
        else
        {
            for(int i = _cpair.second; i < board_tracker.size(); i++)
            {
                if (board_tracker[_cpair.first][i] == MISS)
                {
                    foundpair.first = _cpair.first;
                    foundpair.second= i;
                    break;
                }
                else
                if (board_tracker[_cpair.first][i] == NONE)
                {
                    break;
                }
            }
        }
    }
    else
    if(_cpair.second == _opp_pair.second)
    {
        if (_opp_pair.first - _cpair.first > 0)
        {
            for(int i = _cpair.first; i > 0; i--)
            {
                if (board_tracker[i][_cpair.second] == MISS)
                {
                    foundpair.first = i;
                    foundpair.second= _cpair.second;
                    break;
                }
                if (board_tracker[i][_cpair.second] == NONE)
                {
                    break;
                }
            }
        }
        else
        {
            for(int i = _opp_pair.first; i < board_tracker[0].size(); i++)
            {
                if (board_tracker[i][_opp_pair.second] == MISS)
                {
                    foundpair.first = i;
                    foundpair.second= _opp_pair.second;
                    break;
                }
                if (board_tracker[i][_cpair.second] == NONE)
                {
                    break;
                }
            }
        }
    }
    return foundpair;
}


// this function should return true it it hits the target
bool COMplayer::FireShot(Board* _other_board)
{

    if (random_shot)
    {
        cout << "line: " << __LINE__ << endl;
        if(fireRandShot(_other_board))
        {
            cout << " a random shot hit " << endl;
            random_shot = false;
        }
        else
        {
            random_shot = true;
        }
        cout<< "random_shot: " << random_shot << endl;
    }
    else
    {
        cout << "line: " << __LINE__ << endl;

        if (getCrossPeices(last_shot).size() > 0)
        {
            cout << "line: " << __LINE__ << endl;

            // case shot cross
            auto cur_cross = getCrossPeices(last_shot);
            bool nh_exists = false; // next hit exists
            for (auto icross: cur_cross)
            {
                if (board_tracker[icross.first][icross.second] == HitOrMiss::HIT)
                {
                    nh_exists = true;
                }
            }

            if (nh_exists && last_shots.size() > 1)
            {
                int outlier_min, outlier_max;
                if (last_shot.first == last_shots[0].first)
                {
                    // find min
                    // shoot that first
                    auto ishot = last_shots.begin();
                    for (outlier_min = ishot->second, outlier_max = ishot->second; ishot != last_shots.end(); ishot++)
                    {
                        if (ishot->second < outlier_min)
                        {
                            outlier_min = ishot->second;
                        }
                        if (ishot->second > outlier_max)
                        {
                            outlier_max = ishot->second;
                        }
                        cout << ishot->first << " , " << ishot->second << endl;
                    }
                    cout << "outliers : 1. " << outlier_min << " 2. " << outlier_max << endl;

                    if (outlier_min - 1 >= 0 && \
                        board_tracker[last_shot.first][outlier_min - 1] != HitOrMiss::MISS && \
                        board_tracker[last_shot.first][outlier_min - 1] != HitOrMiss::HIT)
                    {
                        cout << "here" << __LINE__ << endl;
                        makeHit(_other_board, last_shot.first, outlier_min - 1);
                    }
                    else
                    if (outlier_max + 1 < board_tracker[0].size() && \
                        board_tracker[last_shot.first][outlier_max + 1] != HitOrMiss::MISS && \
                        board_tracker[last_shot.first][outlier_max + 1] != HitOrMiss::HIT)
                    {
                        cout << "here" << __LINE__ << endl;
                        makeHit(_other_board, last_shot.first, outlier_max + 1);
                    }
                    else
                    if(outlier_min - 1 >= 0 && outlier_max + 1 < board_tracker[0].size() && \
                        board_tracker[last_shot.first][outlier_max + 1] == HitOrMiss::MISS && \
                        board_tracker[last_shot.first][outlier_min - 1] == HitOrMiss::MISS)
                    {
                        last_shots.clear();
                        random_shot = true;
                        fireRandShot(_other_board);
                    }
                }
                else
                {
                    // do the same thing for the other axis
                }
            }
            else
            {
                makeHit(_other_board, *cur_cross.begin());
            }

        }
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
    cout << "totals: " << total_tiles  << " game left " <<  (float)nothings/(float)total_tiles  * 100 <<"%" << endl;
}

void COMplayer::drawLastHit()
{

    Vector2 point = { static_cast<int>(last_shot.first)*10 + 5 + 550, static_cast<int>(last_shot.second)*10 + 5 + _board.get_y()};

    std::vector<Vector2> v;
    v.push_back(point);

    for(auto t : getCrossPeices(last_shot))
    {
        v.push_back({ static_cast<int>(t.first)*10 + 5 + 550, static_cast<int>(t.second)*10 + 5 + _board.get_y()});
    }

    auto drawthis = v.begin();
    DrawPoly(*drawthis, 6, 4, 0, PINK);

    drawthis++;
    for(drawthis; drawthis < v.end(); drawthis++)
        DrawPoly(*drawthis, 6, 4, 0, GREEN);

}

