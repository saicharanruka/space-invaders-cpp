#ifndef GAME_H
#define GAME_H

#include "spaceship.h"


class Game {
    public:
        Game();
        ~Game();

        void Draw();
        void Update();
        void HandleInput();

    private:
        void DeleteInactiveLasers();
         Spaceship spaceship;
};




#endif