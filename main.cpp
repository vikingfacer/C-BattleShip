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
    board p1gameBoard( 50, 50, '~');
    Ship  p1BattleShip( '#', 10);

    board p2gameBoard( 50, 50, '~');
    Ship  p2BattleShip( '#', 10);

    cout << "Player 1: " << endl;
    cout << "did move work? " << (p1gameBoard.place_ship(&p1BattleShip, 0,0) ? "yes\n" : "no\n");
    p1gameBoard.place_shot(&p2gameBoard,0,0);
    
    cout << "damage: " << p1BattleShip.get_damage() << endl;

    p1gameBoard.draw();

    cout << "damage: " << p2BattleShip.get_damage() << endl;
    cout << "did move work? " << (p2gameBoard.place_ship(&p2BattleShip, 10,10) ? "yes\n" : "no\n");
    p2gameBoard.place_shot(&p1gameBoard,0,0);
    p2gameBoard.place_shot(&p1gameBoard,1,1);

    cout << "damage: " << p2BattleShip.get_damage() << endl;

    p2gameBoard.draw();



    return 0;
}