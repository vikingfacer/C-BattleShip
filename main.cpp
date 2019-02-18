#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <unistd.h>


#include "raylib.h"


#include "board.h"
#include "Ship.h"
#include "player.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

struct shipcord
{
    int x, y;
    orintation h_or_v;
    bool place_ship;
};

class playerInput
{
    // this class is only responsable for user input 
    // it only checks to see if the input is valid game input 
    // if the board is 100 squares it only makes sure input is within 100
public:
playerInput(float _x, float _y, float _max) : 
    x(_x/2),
    y(_y/2), 
    start_x(_x), 
    start_y(_y), 
    max(_max),
    virtical(true) {};

shipcord getInput()
{

    shipcord placement;

    float x_max, y_max;

    if (IsKeyPressed(KEY_RIGHT) && (x <= max)) x += 1;
    else
    if (IsKeyPressed(KEY_LEFT) && (x > 0)) x -= 1;

    if (IsKeyPressed(KEY_DOWN) &&(y <= max)) y += 1;
    else
    if (IsKeyPressed(KEY_UP) && (y > 0)) y -= 1;

    if (IsKeyPressed(KEY_F)) virtical = !virtical;

    if(IsKeyPressed(KEY_ENTER)) placement.place_ship = true;
    else{
        placement.place_ship = false;}


    cout << "x :" << x << " y: " << y << endl;
    
    placement.x = x;
    placement.y = y;
    placement.h_or_v = (virtical ? vertical : horizontal);
    
    return placement;
}

private:
    float x,y, start_x, start_y, max;
    bool virtical;
    
};




int main(int argc, char const *argv[])
{
    InitWindow(1300, 500, "BATTLE SHIP");
    shipcord sp;
    player p1;
    auto cship = p1.ships.begin();

    playerInput  playerIn(0,0, 50);
    bool warning, validMove;
    Board b2(0, 0, 50, 50, '~');

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {


        sp = playerIn.getInput();

        if (cship != p1.ships.end())
        {
            // this is ship placement 
            if (validMove && sp.place_ship)
            {
                cship++;
            }
            else if (validMove)
            {
                p1._board->remove_ship(&(*cship));
            }

            validMove = p1._board->place_ship(&(*cship), sp.x, sp.y, sp.h_or_v);
            // this is the end of the ship placement 
            // warning if not a valid move
            warning = !validMove;
        }
        else
        {
            warning = false;
        }

        BeginDrawing();
        ClearBackground(GRAY);
        b2.draw();

        p1._board->draw();
        if (warning)
            DrawRectangle(0,0, 1300, 500, RED);
            p1._board->draw();



        DrawText("SCORE" , 1100, 20, 40, BLACK);
        DrawText("0000", 1100, 60, 40, BLACK);
        DrawText("HEALTH" , 1100, 120, 40, BLACK);
        DrawText("0", 1100, 160, 40, BLACK);
        DrawText("Direction:" , 1100, 300, 40, BLACK);

        
        EndDrawing();
    }
    return 0;
}





