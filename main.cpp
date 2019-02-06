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

    board gameBoard(50, 50);
    Ship  BattleShip('#', 10);
    Ship  BattleShip2('#', 10);
    Ship  BattleShip3('#', 10);

    cout << "did move work? " << (BattleShip.move(gameBoard, 0,0) ? "yes\n" : "no\n");
    cout << "did move work? " << (BattleShip2.move(gameBoard, 0,0) ? "yes\n" : "no\n");
    cout << "did move work? " << (BattleShip3.move(gameBoard, 50,1, vertical) ? "yes\n" : "no\n");

    gameBoard.draw();



    return 0;
}