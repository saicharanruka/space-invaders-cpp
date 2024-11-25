#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "raylib.h"

class Spaceship {

    public :
        Spaceship();
        ~Spaceship();

        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireLaser();
    
    private :
        Texture2D image;
        Vector2 position;


};

#endif