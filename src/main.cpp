#include "raylib.h"
#include "game.h"
#include <string>

void LogoScreen();

enum class GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING };
GameScreen currentScreen = GameScreen::LOGO;

constexpr Color grey = BLACK;

const int screenWidth = 800;
const int screenHeight = 800;

int logoPositionX = screenWidth/2 - 128;
int logoPositionY = screenHeight/2 - 128;

int framesCounter = 0;
int lettersCount = 0;

int topSideRecWidth = 16;
int leftSideRecHeight = 16;

int bottomSideRecWidth = 16;
int rightSideRecHeight = 16;

int state = 0;                  // Tracking animation states (State Machine)
float alpha = 1.0f;             // Useful for fading







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
        switch (currentScreen)
        {
        case (GameScreen::LOGO):
            LogoScreen();
            break;
        case GameScreen::GAMEPLAY:
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
        default:
            break;
        }
    }
  

    CloseWindow();
    CloseAudioDevice();

    return 0;
}

void LogoScreen()
{
        // Update
        //----------------------------------------------------------------------------------
        if (state == 0)                 // State 0: Small box blinking
        {
            framesCounter++;

            if (framesCounter == 120)
            {
                state = 1;
                framesCounter = 0;      // Reset counter... will be used later...
            }
        }
        else if (state == 1)            // State 1: Top and left bars growing
        {
            topSideRecWidth += 4;
            leftSideRecHeight += 4;

            if (topSideRecWidth == 256) state = 2;
        }
        else if (state == 2)            // State 2: Bottom and right bars growing
        {
            bottomSideRecWidth += 4;
            rightSideRecHeight += 4;

            if (bottomSideRecWidth == 256) state = 3;
        }
        else if (state == 3)            // State 3: Letters appearing (one by one)
        {
            framesCounter++;

            if (framesCounter/12)       // Every 12 frames, one more letter!
            {
                lettersCount++;
                framesCounter = 0;
            }

            if (lettersCount >= 10)     // When all letters have appeared, just fade out everything
            {
                alpha -= 0.02f;

                if (alpha <= 0.0f)
                {
                    alpha = 0.0f;
                    state = 4;
                }
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(grey);

            if (state == 0)
            {
                if ((framesCounter/15)%2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, GREEN);
            }
            else if (state == 1)
            {
                DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, GREEN);
                DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, GREEN);
            }
            else if (state == 2)
            {
                DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, GREEN);
                DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, GREEN);

                DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, GREEN);
                DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, GREEN);
            }
            else if (state == 3)
            {
                DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(GREEN, alpha));
                DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(GREEN, alpha));

                DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(GREEN, alpha));
                DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(GREEN, alpha));

                DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, Fade(grey, alpha));

                DrawText(TextSubtext("raylib", 0, lettersCount), GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 50, Fade(GREEN, alpha));
            }
            else if (state == 4)
            {
                currentScreen = GameScreen::GAMEPLAY;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }