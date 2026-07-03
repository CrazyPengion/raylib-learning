// Basic snake in dark mode. First real game in Raylib and usage of drawing blocks.
// Attempt to make a tiny executable trough lack of libraries such as <iostream>.

ideas: // supposed to cause error - so that I don't forget about it when I get to doing it.
/*
Make a list of previous head positions
each block moves to list[i-blockNumber]

death: if hit wall or is in pos of list[i-1] to list[i-blocknumber] - die
*/

#include <iostream> // DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG
#include "raylib.h"
// GLOBAL VARIABLES
constexpr int windowWidth{ 1000 };
constexpr int windowHeight{ 1000 };
constexpr int gridSize{ 50 };

int direction{ 0 }; // 0 = up , 1 = left , 2 = down , 3 = right (WASD)
int lastDirection{ 0 }; // stops a bug that allows you to switch directions and then go backwards between movements
int posX{400};
int posY{400};
double tick{};

// FUNCTIONS
void getUserInput();
void calculateMovement();
void deathBringer();
void foodManager();
void updateScreen();

int main() 
{
    // WINDOW
    InitWindow(windowWidth, windowHeight, "Snake");
    SetTargetFPS(60);

    // MAIN LOOP
    while (!WindowShouldClose())
    {
        getUserInput();
        calculateMovement();
        //foodManager();
        updateScreen();
    }
    
    CloseWindow();
    return 0;
}

// GET DIRECTION OF SNAKE MOVEMENT
void getUserInput()
{
    if ((IsKeyPressed(KEY_W) or IsKeyPressed(KEY_UP)) and !(lastDirection == 2))
    {
        direction = 0;
    }

    if ((IsKeyPressed(KEY_A) or IsKeyPressed(KEY_LEFT)) and !(lastDirection == 3)) // IsKeyPressed over IsKeyDown to avoid double clicks
    {
        direction = 1;
    }

    if ((IsKeyPressed(KEY_S) or IsKeyPressed(KEY_DOWN)) and !(lastDirection == 0))
    {
        direction = 2;
    }

    if ((IsKeyPressed(KEY_D) or IsKeyPressed(KEY_RIGHT)) and !(lastDirection == 1))
    {
        direction = 3;
    }
}

// CALCULATE MOVEMENT
void calculateMovement()
{
    tick += GetFrameTime();
    std::cout << tick << "\n";
    if (tick >= 0.3)
    {
        lastDirection = direction; 

        if (direction == 0) //up
        {
            posY -= gridSize;
        }
        if (direction == 2) //down
        {
            posY += gridSize;
        }

        if (direction == 1) //left
        {
            posX -= gridSize;
        }
        if (direction == 3) //right
        {
            posX += gridSize;
        }

        tick = 0;
    }
}

// deathbringer - if hits self / wall = dead

// food - if food collected = spawn new random food + expand snake

void updateScreen()
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangle(posX, posY, gridSize, gridSize, PURPLE);
    EndDrawing();
}