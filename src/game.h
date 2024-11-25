#ifndef GAME_H
#define GAME_H

#include "spaceship.h"
#include "obstacle.h"
#include "alien.h"
#include "mystery-ship.h"


class Game {
    public:
        Game();
        ~Game();

        void Draw();
        void Update();
        void HandleInput();
        void GameOver();
        

        int lives;
        bool running;

        int score;
        int highscore = 0;

        Music music;


    private:
        void CheckForCollisions();
        void DeleteInactiveLasers();

        std::vector<Obstacle> CreateObstacles();
        std::vector<Alien> CreateAliens();
        void MoveAliens();
        void MoveDownAliens(int dist);
        void AlienShootLaser();


         Spaceship spaceship;
         std::vector<Obstacle> obstacles;
         std::vector<Alien> aliens;

         int aliensDirection;
         std::vector<Laser> alienLasers;
         constexpr static float alienLaserShootInterval = 0.35;
         float timeLastAlienFired;

         MysteryShip mship;
         float mysteryShipSpwanInterval;
         float timeLastSpawn;

         void Reset();
         void InitGame();
         void checkForHighscore();

         Sound explosionSound;
};




#endif