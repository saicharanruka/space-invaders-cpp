#ifndef LASER_H
#define LASER_H

#include <raylib.h>

class Laser
{
public:
    Laser(Vector2 position, int speed);
    // ~Laser();

    void Draw();
    void Update();
    bool active;

private:
    Vector2 position;
    int speed;
    

};






#endif