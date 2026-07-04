// Basic snake in dark mode. First real game in Raylib and usage of drawing blocks.
// Attempt to make a tiny executable trough lack of libraries such as <iostream>.

#include <iostream> // DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG
#include "raylib.h"
#include <list>

// GLOBAL VARIABLES
constexpr int windowSize{ 1000 };
constexpr int gridSize{ 50 };

            //movement
int direction{ -1 }; // 0 = up , 1 = left , 2 = down , 3 = right (WASD)
int lastDirection{ -1 }; // stops a bug that allows you to switch directions and then go backwards between movements
int posX{ (windowSize / 2) };
int posY{ (windowSize / 2) };
bool moved = false;

int foodX{-1}; //food
int foodY{-1};

double tick{0}; //time

int size{ 5 };
int highScore;

// FUNCTIONS
void getUserInput();
void calculateMovement();
void deathBringer(int tempX, int tempY); //called by calculateMovement()
void foodCollector();
void foodSpawner(); //called by foodColletor()
void updateScreen();

int main() 
{
    // WINDOW
    InitWindow(windowSize, windowSize, "Snake");
    SetTargetFPS(100);

    // MAIN LOOP
    while (!WindowShouldClose())
    {
        getUserInput();
        calculateMovement();
        foodSpawner();
        updateScreen();
    }
    
    CloseWindow();
    return 0;
}

// GET DIRECTION OF SNAKE MOVEMENT
void getUserInput()
{
    if ((IsKeyPressed(KEY_W) or IsKeyPressed(KEY_UP))) // IsKeyPressed over IsKeyDown to avoid double clicks
    {
        if ((size == 1) or (size != 1 and !(lastDirection == 2))) // disallows going back if you're not a single block (instant death)
        {
            direction = 0;
            moved = true;
        }
    }

    if ((IsKeyPressed(KEY_A) or IsKeyPressed(KEY_LEFT))) 
    {
        if ((size == 1) or (size != 1 and !(lastDirection == 2)))
        {
            direction = 1;
            moved = true;
        }
    }

    if ((IsKeyPressed(KEY_S) or IsKeyPressed(KEY_DOWN)))
    {
        if ((size == 1) or (size != 1 and !(lastDirection == 2)))
        {
            direction = 2;
            moved = true;
        }
    }

    if ((IsKeyPressed(KEY_D) or IsKeyPressed(KEY_RIGHT)))
    {
        if ((size == 1) or (size != 1 and !(lastDirection == 2)))
        {
            direction = 3;
            moved = true;
        }
    }
}

// CALCULATE MOVEMENT
void calculateMovement()
{
    tick += GetFrameTime();
    if (tick >= 0.1) //0.3
    {
        int tempX{ posX };
        int tempY{ posY };

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

        // if hit wall
        if ((posX < 0) or (posX > (windowSize - gridSize)) or (posY < 0) or (posY > (windowSize - gridSize)))
        {
            deathBringer(tempX, tempY);
        }
    }
}

// DEATH
void deathBringer(int tempX, int tempY)
{
    if (size > highScore)
    {
        highScore = size;
    }

    BeginDrawing();
    DrawRectangle(tempX, tempY, gridSize, gridSize, RED);
    EndDrawing();

    WaitTime(1);

    direction = -1; // 0 = up , 1 = left , 2 = down , 3 = right (WASD)
    lastDirection = -1;
    posX = (windowSize / 2);
    posY = (windowSize / 2);
    size = 1;
    tick = 0;
    moved = false;
}

// FOOD SPAWNER
void foodSpawner()
{
    // get random cords
    int tempX{ 10 * GetRandomValue(0, (windowSize / gridSize)) };
    int tempY{ 10 * GetRandomValue(0, (windowSize / gridSize)) };
    // make sure it isn't in the snake
    while (tempX == posX) { int tempX = (10 * GetRandomValue(0, (windowSize / gridSize))); }
    while (tempY == posY) { int tempY = (10 * GetRandomValue(0, (windowSize / gridSize))); }
    // make it food pos
    foodX = tempX;
    foodY = tempY;
}

// FOOD COLLECTOR
void foodCollector()
{
    // collect food
    if (posX == foodX and posY == foodY)
    {
        ++size;
        foodSpawner();
    }
}

void updateScreen()
{
    BeginDrawing();
    ClearBackground(BLACK);

    //draws background grid
    for (int i = 0; i < (windowSize / gridSize); i++)
    {
        DrawRectangle(((i * gridSize) - 1), 0, 2, 1000, DARKGRAY);
        DrawRectangle(0, ((i * gridSize) - 1), 1000, 2, DARKGRAY);
    }

    if (moved == false)
    {
        // display highScore
    }

    //draws food
    DrawRectangle(foodX, foodY, gridSize, gridSize, YELLOW);

    //draws snake (user)
    DrawRectangle(posX, posY, gridSize, gridSize, PURPLE);
    //tail


    EndDrawing();
}

stuff:
1. make highscore display
2. make tail visible
3. make it a death to slam against tail
  -->  could only save size-1 previous cords, check if youre hitting any of them