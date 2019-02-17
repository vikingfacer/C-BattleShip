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

	player p1;
	shipcord sp;
	playerInput  playerIn(0,0, 50);
	bool validMove;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
    	if (validMove)
	        p1._board->remove_ship(&p1.ships[0]);

    
    	sp = playerIn.getInput();

        validMove = p1._board->place_ship(&p1.ships[0],sp.x, sp.y, sp.h_or_v);


        BeginDrawing();
        ClearBackground(RAYWHITE);

        p1._board->draw();
        if (!validMove)
        	DrawRectangle(0,0, 1300, 500, RED);
        	p1._board->draw();

		EndDrawing();
    }
    return 0;
}





