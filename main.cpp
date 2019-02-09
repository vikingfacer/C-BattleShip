#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>


#include <boost/regex.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "board.h"
#include "Ship.h"


using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(int argc, char const *argv[])
{
    board gameBoard( 50, 50, '~');
    Ship  BattleShip( '#', 10);

    cout << "did move work? " << (gameBoard.place_ship(&BattleShip, 0,0) ? "yes\n" : "no\n");
    gameBoard.place_shot(0,0);
    cout << "damage: " << BattleShip.get_damage() << endl;
    gameBoard.draw();



    return 0;
}