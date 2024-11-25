#include "raylib.h"
#include "game.h"
#include <string>

constexpr int g_offset = 50;
constexpr int g_windowWidth = 750;
constexpr int g_windowHeight = 700;
constexpr Color grey = {29, 29, 27, 255};


std::string FormatWithLeadingZeroes(int num, int width) {
    std::string numberText = std::to_string(num);
    int leadingZeroes = width - numberText.length();
    return numberText = std::string(leadingZeroes, '0') + numberText;

}



int main(void)
{
    InitWindow(800, 800, "Space Invaders C++");
    InitAudioDevice();

    SetTargetFPS(60);
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("graphics/spaceship.png");

    Game game;
 

    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        game.Update();


        BeginDrawing();

            ClearBackground(grey);
            DrawRectangleRoundedLines({10,10,780, 780}, 0.18f, 20, YELLOW);
            DrawLineEx({25,730}, {775,730}, 3, YELLOW);

            if (game.running)
                DrawTextEx(font, "LEVEL 01", {600, 740}, 24, 2, YELLOW);
            else
                DrawTextEx(font, "GAME OVER", {600, 740}, 24, 2, YELLOW);



            // display lives
            float x = 50.0;
            for (int i = 0; i < game.lives; i++)
            {

                DrawTextureV(spaceshipImage, {x, 745}, WHITE);
                x += 50;
            }
            
            DrawTextEx(font, "SCORE", {50,15}, 24, 2, YELLOW);
            std::string scoreText = FormatWithLeadingZeroes(game.score, 5);
            DrawTextEx(font, scoreText.c_str(), {50, 40}, 24, 2, YELLOW);

            DrawTextEx(font, "HIGH-SCORE", {570,15}, 24, 2, YELLOW);
            std::string highscoreText = FormatWithLeadingZeroes(game.highscore, 5);
            DrawTextEx(font, highscoreText.c_str(), {655, 40}, 24, 2, YELLOW);



            
            

            game.Draw();
            
        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}