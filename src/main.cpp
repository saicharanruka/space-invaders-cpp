#include "raylib.h"
#include "game.h"

constexpr int g_offset = 50;
constexpr int g_windowWidth = 750;
constexpr int g_windowHeight = 700;
constexpr Color grey = {29, 29, 27, 255};

int main(void)
{
    InitWindow(800, 800, "Space Invaders C++");
    SetTargetFPS(60);

    Game game;
 

    while (!WindowShouldClose())
    {
        game.HandleInput();
        game.Update();


        BeginDrawing();

            ClearBackground(grey);
            DrawRectangleRoundedLines({10,10,780, 780}, 0.18f, 20, YELLOW);
            DrawLineEx({25,730}, {775,730}, 3, YELLOW);
            game.Draw();
            
        EndDrawing();
    }

    CloseWindow();

    return 0;
}