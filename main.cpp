#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>

#include "raylib.h"


#include "board.h"
#include "Ship.h"
#include "player.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class playerInput
{
public:
playerInput(float _x, float _y) : x(_x/2), y(_y/2), start_x(_x), start_y(_y) {};

void draw(int size)
{
	float _x = x, _y = y;
	DrawRectangle(_x * 10, _y * 10, 90, 90, BLACK);

};

int* getInput()
{

	if (IsKeyDown(KEY_RIGHT) && (x < start_x)) x += 1;
	else
	if (IsKeyDown(KEY_LEFT) && (x > 0))	x -= 1;

	if (IsKeyDown(KEY_DOWN) &&(y < start_y))	y += 1;
	else
	if (IsKeyDown(KEY_UP) && (y > 0))	y -= 1;

	int arr[2] = {x, y};

	cout << "x :" << x << " y: " << y << endl;
	return arr;
}
private:
	float x,y, start_x, start_y;
	
};



int main(int argc, char const *argv[])
{
	InitWindow(500, 500, "BATTLE SHIP");

	player p1;

	playerInput  playerIn(500,500);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

    	playerIn.getInput();


        BeginDrawing();
        ClearBackground(RAYWHITE);
        p1._board->draw();

        playerIn.draw(10);



		EndDrawing();
    }
	p1._board->draw();
    return 0;
}





