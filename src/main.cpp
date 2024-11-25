#include "raylib.h"
#include "game.h"

constexpr int g_windowWidth = 750;
constexpr int g_windowHeight = 700;
constexpr Color grey = {29, 29, 27, 255};

int main(void)
{
    InitWindow(g_windowWidth, g_windowHeight, "Space Invaders C++");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
        game.HandleInput();


        BeginDrawing();
            ClearBackground(grey);
            game.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}