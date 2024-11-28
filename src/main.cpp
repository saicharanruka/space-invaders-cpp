#include "raylib.h"
#include "game.h"
#include <string>

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

constexpr Color grey = BLACK;


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
    GameScreen currentScreen = LOGO;
 

    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        game.Update();


        BeginDrawing();

            ClearBackground(grey);
            DrawRectangleRoundedLines({10,10,780, 780}, 0.18f, 20, GREEN);
            DrawLineEx({25,730}, {775,730}, 3, GREEN);

            if (game.running)
                DrawTextEx(font, "LEVEL 01", {600, 740}, 24, 2, GREEN);
            else
                DrawTextEx(font, "GAME OVER", {600, 740}, 24, 2, GREEN);



            // display lives
            float x = 50.0;
            for (int i = 0; i < game.lives; i++)
            {

                DrawTextureV(spaceshipImage, {x, 745}, WHITE);
                x += 50;
            }
            
            DrawTextEx(font, "SCORE", {50,15}, 24, 2, GREEN);
            std::string scoreText = FormatWithLeadingZeroes(game.score, 5);
            DrawTextEx(font, scoreText.c_str(), {50, 40}, 24, 2, GREEN);

            DrawTextEx(font, "HIGH-SCORE", {570,15}, 24, 2, GREEN);
            std::string highscoreText = FormatWithLeadingZeroes(game.highscore, 5);
            DrawTextEx(font, highscoreText.c_str(), {655, 40}, 24, 2, GREEN);



            
            

            game.Draw();
            
        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}