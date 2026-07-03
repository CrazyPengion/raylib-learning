// 28.06.2026 - first RayLib program.
// Gemini was used for setup and with help getting it to run (removed while True ; added begin/end drawing)


#include "raylib.h"

int windowWidth{ 300 };
int windowHeight{ 200 };
bool changedWindowSize{ false };

int main() {
    InitWindow(windowWidth, windowHeight, "WASD"); // create window
    SetTargetFPS(60); // max fps
    Image icon = LoadImage("Icon.png");
    SetWindowIcon(icon); // make icon into Icon.png (Resource Files)

    while (!WindowShouldClose()) // 1. Use this instead of true
    {
        changedWindowSize = false;

        if (IsKeyDown(KEY_W))
        {
            windowHeight -= 10;
            SetWindowSize(windowWidth, windowHeight); // 3. IMPORTANT: Tell OS to resize
        }

        if (IsKeyDown(KEY_S))
        {
            windowHeight += 10;
            SetWindowSize(windowWidth, windowHeight);
        }

        if (IsKeyDown(KEY_D))
        {
            windowWidth += 10;
            SetWindowSize(windowWidth, windowHeight);
        }

        if (IsKeyDown(KEY_A))
        {
            windowWidth -= 10;
            SetWindowSize(windowWidth, windowHeight);
        }

        // 4. Drawing logic (Every frame needs these!)
        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();
    UnloadImage(icon);
    return 0;
}