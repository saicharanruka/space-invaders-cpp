#include "game.h"
#include <iostream>

Game::Game()
{
    InitGame();
}

Game::~Game()
{
    Alien::UnloadImages();
}

void Game::InitGame()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = GetTime();


    timeLastSpawn = 0.0;
    mysteryShipSpwanInterval = GetRandomValue(10,20);
    lives = 3;
    running = true;

}

void Game::Reset() {
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();

}


void Game::Update() {

    if (running) {
            double currentTime = GetTime();
    if (currentTime - timeLastSpawn > mysteryShipSpwanInterval) {
        mship.Spawn();
        timeLastSpawn = GetTime();
        mysteryShipSpwanInterval = GetRandomValue(10,20);
    }



    for(auto& laser: spaceship.lasers) {
        laser.Update();
    }

    mship.Update();
    MoveAliens();
    CheckForCollisions();

    AlienShootLaser();
    for(auto& alaser : alienLasers) {
        alaser.Update();
    }

    DeleteInactiveLasers();

    }
    else if (IsKeyDown(KEY_ENTER)) {
        Reset(); 
        InitGame();
    }


    

}

void Game::Draw() {
    spaceship.Draw();

    for(auto& laser: spaceship.lasers) {
        laser.Draw();
    }

    for (auto& obstacle:obstacles) {
        obstacle.Draw();
    }
    for (auto& alien:aliens) {
        alien.Draw();
    }
    for(auto& laser: alienLasers) {
        laser.Draw();
    }
    mship.Draw();
}


void Game::HandleInput() {
    if (running) {
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
}

void Game::GameOver() {
    std::cout << "Game over!" << '\n';
    running = false;
}

void Game::CheckForCollisions()
{
    // Spaceship lasers check -------------------------------------------

    // with aliens
    for (auto& laser : spaceship.lasers) {
        auto it = aliens.begin();
        while (it != aliens.end()) {
            if (CheckCollisionRecs(it -> getRect(), laser.getRect())) 
            {
                it = aliens.erase(it);
                laser.active = false;
            }
            else 
                ++it;
            
        }
        // with obstacles
        for (auto& obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                    if(CheckCollisionRecs(it -> getRect(),laser.getRect())) {
                        it = obstacle.blocks.erase(it);
                        laser.active = false;
                    }
                    else
                        ++it;
                }
        }

        // with mystery ship
        if (CheckCollisionRecs(mship.getRect(), laser.getRect())) {
            mship.alive = false;
            laser.active = false;
        }
    }


     // Alien lasers check ------------------------------- alaser = Alien Laser

     
     for (auto& alaser : alienLasers) {
        // with spaceship
        if (CheckCollisionRecs(spaceship.getRect(), alaser.getRect())) {
            alaser.active = false;
            lives--;
            if (lives == 0) {
                GameOver();
            }
        }

        // with obstacles
        for (auto& obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if(CheckCollisionRecs(alaser.getRect(), it -> getRect())) {
                    it = obstacle.blocks.erase(it);
                    alaser.active = false;
                }
                else
                    ++it;
            }
     }   
     }

     // Alien collision ---------------------------------------------------

     for(auto& alien: aliens)  {
        // with obstacle
        for(auto& obstacle: obstacles) 
        {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(alien.getRect(), it->getRect())) {
                    it = obstacle.blocks.erase(it);
                }else {
                    ++it;
                }
            }
        }

        // with player
        if(CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
            GameOver();
        }
     }

}

void Game::DeleteInactiveLasers()
{

    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
        if(!it -> active) {
            it = spaceship.lasers.erase(it);

        } else {
            ++it;
        }
    }

        for (auto it = alienLasers.begin(); it != alienLasers.end();) {
        if(!it -> active) {
            it = alienLasers.erase(it);

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
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100 - 100)})); // 100 offset for ui
    }
    
    return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 11; col++)
        {
            int alienType;
            if (row == 0) {
                alienType = 3;
            }
            else if (row ==1 || row == 2) {
                alienType = 2;
            }
            else {
                alienType = 1;
            }




            float x = 75 + col * 55; // x offest = 75
            float y = 110 + row * 55; // y offset = 110
            aliens.push_back(Alien(alienType,{x,y}));
        }
        
    }

    return aliens;
}

void Game::MoveAliens() {
    for(auto& alien : aliens) {
        if(alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25)  {
            aliensDirection = -1;
            MoveDownAliens(4);
        }
        else if (alien.position.x < 25) {
            aliensDirection = 1;
            MoveDownAliens(5);
        }


        alien.Update(aliensDirection);
    }


}

void Game::MoveDownAliens(int dist) {
    for(auto& alien : aliens) {
        alien.position.y += dist;
    }
}

void Game::AlienShootLaser() {

    double currentTime = GetTime();

    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {

        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien alien = aliens[randomIndex];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type - 1].width/2, 
                alien.position.y + alien.alienImages[alien.type - 1].height},6, BLUE ));
        
        timeLastAlienFired = GetTime();
    }
}


