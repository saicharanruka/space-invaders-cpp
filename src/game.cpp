#include "game.h"
#include <iostream>

Game::Game()
{
    obstacles = CreateObstacles();

}

Game::~Game()
{
}



void Game::Update() {
    for(auto& laser: spaceship.lasers) {
        laser.Update();
    }
    DeleteInactiveLasers();

}

void Game::Draw() {
    spaceship.Draw();

    for(auto& laser: spaceship.lasers) {
        laser.Draw();
    }

    for (auto& obstacle:obstacles) {
        obstacle.Draw();
    }

}


void Game::HandleInput() {
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        spaceship.MoveLeft();
    }

    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        spaceship.MoveRight();
    }
    else if (IsKeyDown(KEY_SPACE)) 
{
        spaceship.FireLaser();
    }
}

void Game::DeleteInactiveLasers() {

    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
        if(!it -> active) {
            it = spaceship.lasers.erase(it);

        } else {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
    static constexpr int OBSTACLES_COUNT = 4;
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (OBSTACLES_COUNT* obstacleWidth))/5; // 5 gaps

    for (int i = 0; i < OBSTACLES_COUNT; i++)
    {
        float offsetX = (i+1)*gap + i*obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100)}));
    }
    
    return obstacles;
}
