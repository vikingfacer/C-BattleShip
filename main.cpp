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

// This should return keyboard state only
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
    virtical(true),
    music(true)
{};

void draw(Board* _board)
{
    DrawCircle( (x+ _board->get_x()) * 10 + 5, (y + _board->get_y()) * 10 + 5, 5, YELLOW);
}

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

    if(IsKeyPressed(KEY_M)) music = !music;


    cout << "x :" << x << " y: " << y << " music: "<< music<< endl;
    
    placement.x = x;
    placement.y = y;
    placement.h_or_v = (virtical ? vertical : horizontal);
    
    return placement;
}

const bool getMusic() {return music;};

private:
    float x,y, start_x, start_y, max;
    bool virtical, music;
};




//  I want to have the game stages in a vector of functions
// so each stage can be a function 
// this would be more flexable then a ifelse stage1, stage2, ect...
// std::vector<bool (*)()> GameStages;

enum GAMESTAGE
{
    STAGE0 = 0,
    STAGE1,
    STAGE2,
    STAGE3,
};


int main(int argc, char const *argv[])
{
    InitWindow(1300, 500, "BATTLE SHIP");
    InitAudioDevice();


    Music music = LoadMusicStream("resources/Azerbaijan_national_anthem_(vocal_version).ogg");
    PlayMusicStream(music);


    GAMESTAGE cstage = STAGE1; 


    shipcord sp;
    player p1;
    auto cship = p1.ships.begin();



    playerInput  playerIn(0,0, 50);
    bool warning, playing_music;
    Vector2 point = {300,300};
    // dummy targets 
    Board b2(0, 0, 50, 50, '~');
    Ship  s1('#', 10);
    b2.place_ship(&s1, 20, 20, horizontal);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        sp = playerIn.getInput();

    	if(playerIn.getMusic())
    	{
        	UpdateMusicStream(music);        // Update music buffer with new stream data
    	}


        switch(cstage)
        {
            case STAGE1:
                warning = p1.PlaceShip(cship,sp);
                if (cship == p1.ships.end())
                {
                	cstage = STAGE2;
                }
            break;
            case STAGE2:
                // shot opponent 
            	if (sp.place_ship)
            	{
	            	p1._board->place_shot(&b2, sp.x, sp.y);
    			}
                // get shot by opponent
            break;
        }
    



        BeginDrawing();
        
	        if (warning)
	        {
	            ClearBackground(RED);
	        }else
	        {
	            ClearBackground(GRAY);
	        }

	        b2.draw();
	        p1._board->draw();

	        playerIn.draw(p1._board);
	        playerIn.draw(&b2);

	        DrawText("SCORE" , 1100, 20, 40, BLACK);
	        DrawText("0000", 1100, 60, 40, BLACK);
	        DrawText("HEALTH" , 1100, 120, 40, BLACK);
	        DrawText("0", 1100, 160, 40, BLACK);
	        DrawText("Direction:" , 1100, 300, 40, BLACK);

        EndDrawing();
    }
    return 0;
}





