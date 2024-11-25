#ifndef LASER_H
#define LASER_H

#include <raylib.h>

class Laser
{
public:
    Laser(Vector2 position, int speed, Color color);

    void Draw();
    void Update();
    Rectangle getRect();

    bool active;
    Color color;

private:
    Vector2 position;
    int speed;
    

};






#endif