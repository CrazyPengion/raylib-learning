// Basic snake in dark mode. First real game in Raylib and usage of drawing blocks.
// Attempt to make a tiny executable trough lack of libraries such as <iostream>.

#include "raylib.h" //game
#include <vector> //tail movement
#include <deque> //^
#include <string> //highscore message

// GLOBAL VARIABLES
constexpr int windowSize{ 1000 };
constexpr int gridSize{ 50 };

            //movement
int direction{ -1 }; // 0 = up , 1 = left , 2 = down , 3 = right (WASD)
int lastDirection{ -1 }; // stops a bug that allows you to switch directions and then go backwards between movements
int posX{ (windowSize / 2) };
int posY{ (windowSize / 2) };
std::deque<Vector2> oldPositionHistory;
bool moved = false;

int foodX{-1}; //food
int foodY{-1};

double tick{0}; //time

int size{ 1 };
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

    foodSpawner();
    // MAIN LOOP
    while (!WindowShouldClose())
    {
        getUserInput();
        calculateMovement();
        foodCollector();
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
        if ((size == 1) or (size != 1 and !(lastDirection == 3)))
        {
            direction = 1;
            moved = true;
        }
    }

    if ((IsKeyPressed(KEY_S) or IsKeyPressed(KEY_DOWN)))
    {
        if ((size == 1) or (size != 1 and !(lastDirection == 0)))
        {
            direction = 2;
            moved = true;
        }
    }

    if ((IsKeyPressed(KEY_D) or IsKeyPressed(KEY_RIGHT)))
    {
        if ((size == 1) or (size != 1 and !(lastDirection == 1)))
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
        // save old location to history
        oldPositionHistory.push_front(Vector2({ (float)posX, (float)posY })); 
                                    // converts 2 ints to floats, as that's what vectors store
                                    // converts the floats into a vector, as that's what the deque stores
        // remove old positions if there are more than snake parts
        if ((int)oldPositionHistory.size() > (size - 1)) // convert to int as it returns unsigned int (removes possible compiler warning)
        {
            oldPositionHistory.pop_back();
        }

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

        // if hit self
        if (size > 1)
        {
            for (const Vector2& pos : oldPositionHistory) // explanation in updateScreen()
            {
                if (posX == pos.x and posY == pos.y)
                {
                    deathBringer(tempX, tempY);
                    break;
                }
            }
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
    oldPositionHistory.clear();
    foodSpawner();
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

// FOOD SPAWNER
void foodSpawner()
{
    // get random cords
    int tempX{ gridSize * GetRandomValue(0, (windowSize / gridSize - 1)) }; // -1 to keep inside window
    int tempY{ gridSize * GetRandomValue(0, (windowSize / gridSize - 1)) };

    // make sure it isn't in the snake
    while (tempX == posX) 
    { 
        tempX = (gridSize * GetRandomValue(0, (windowSize / gridSize - 1)));
    }

    while (tempY == posY) 
    { 
        tempY = (gridSize * GetRandomValue(0, (windowSize / gridSize - 1)));
    }

    // make sure it isn't in the tail
    for (const Vector2& pos : oldPositionHistory)
    {
        if (pos.x == tempX and pos.y == tempY)
        {
            tempX = (gridSize * GetRandomValue(0, (windowSize / gridSize - 1)));
            tempY = (gridSize * GetRandomValue(0, (windowSize / gridSize - 1)));
        }
    }

    // make it food pos
    foodX = tempX;
    foodY = tempY;
}

// UPDATES SCREEN
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

    //draws food
    DrawRectangle(foodX, foodY, gridSize, gridSize, YELLOW);

    //draws snake (user)
    DrawRectangle(posX, posY, gridSize, gridSize, PURPLE);
    //tail
    for (const Vector2& pos : oldPositionHistory) // pos gets the value of each unit of oPH one by one ; & makes it not copy over a value, but rather is a reference to the original (better performance because of no copying) ; const for compiler optimisations
    { 
        DrawRectangle(pos.x, pos.y, gridSize - 2, gridSize - 2, DARKBLUE);
    } 

    //draws highscore ( at end to overlap food/grid)
    if (moved == false)
    {
        std::string highscoreMessage{ std::to_string(highScore) };
        DrawText(TextFormat("Highscore: %s", highscoreMessage), 10, 10, (windowSize / 26), WHITE);
    }

    EndDrawing();
}