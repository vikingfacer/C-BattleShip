#include "COMplayer.h"



COMplayer::COMplayer() :
    x_dist(std::uniform_int_distribution<int>(0, _board.get_row()-1)),
    y_dist(std::uniform_int_distribution<int>(0, _board.get_column()-1)),
    gen(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())),
    board_tracker(vector<vector<HitOrMiss>>(_board.get_row(), vector<HitOrMiss>(_board.get_column(), HitOrMiss::NONE))),
    random_shot(true),
    last_shot(pair<int,int>())
{};


COMplayer::COMplayer(int x, int y) : player( x, y),
    x_dist(std::uniform_int_distribution<int>(0, _board.get_row()-1)),
    y_dist(std::uniform_int_distribution<int>(0, _board.get_column()-1)),
    gen(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())),
    board_tracker(vector<vector<HitOrMiss>>(_board.get_row(), vector<HitOrMiss>(_board.get_column(), HitOrMiss::NONE))),
    random_shot(true),
    last_shot(pair<int,int>())

{};


bool COMplayer::PlaceShip( std::vector<Ship>::iterator& _cship)
{
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


bool COMplayer::FireShot(Board* _other_board)
{
    int gen_x = x_dist(gen);
    int gen_y = y_dist(gen);
    int count = 0;

    auto ctile = _other_board->get(gen_x, gen_y);

    // pick a random tile if the last hit list is empty
    // otherwise figure out a tile to use from the list of hits
    // could add difficultly levels to the com here

    if (random_shot)
    {
        // this should be a for loop
        while(ctile->get_is_shot() && count < 5)
        {
            gen_x = x_dist(gen);
            gen_y = y_dist(gen);
            _other_board->get(gen_x, gen_y);
            cout << "in loop"<< endl;
            count++;
        }

        if (_board.place_shot(_other_board, gen_x, gen_y))
        {
            random_shot = false;
            last_shot.first = gen_x;
            last_shot.second= gen_y;
        }

        // we return true if the shot is successful
        return true;
    }
    else
    {



        random_shot = true;
    }
    return false;
}
