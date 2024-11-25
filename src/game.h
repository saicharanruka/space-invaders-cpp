#ifndef GAME_H
#define GAME_H

#include "spaceship.h"
#include "obstacle.h"


class Game {
    public:
        Game();
        ~Game();

        void Draw();
        void Update();
        void HandleInput();

    private:
        void DeleteInactiveLasers();

        std::vector<Obstacle> CreateObstacles();
         Spaceship spaceship;
         std::vector<Obstacle> obstacles;
};




#endif