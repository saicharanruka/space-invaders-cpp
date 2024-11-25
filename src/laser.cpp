#include "laser.h"

Laser::Laser(Vector2 position, int speed, Color color)
{
    this -> position = position;
    this -> speed = speed;
    this -> color = color;
    active = true;
}

void Laser::Draw() {
    if (active)
        DrawRectangle(position.x, position.y, 4, 15, color);
}

void Laser::Update() {
    position.y += speed;

    if (active) {
        if (position.y > GetScreenHeight() - 100 || position.y < 25) {
            active = false;
        }
    }
}

Rectangle Laser::getRect()
{
    return {position.x, position.y, 4, 15};
}
