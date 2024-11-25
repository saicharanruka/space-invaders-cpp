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
         Spaceship spaceship;
};




#endif