#include "spaceship.h"

Spaceship::Spaceship()
{
    image = LoadTexture("graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height - 100; // moved up due to ui
    lastFireTime = 0.0;
    laserSound = LoadSound("sounds/laser.ogg");
}

Spaceship::~Spaceship() {

    UnloadTexture(image);
}


void Spaceship::Draw() {
    DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft() {
    position.x -= 7;

    if (position.x < 25)
        position.x = 25;
}


void Spaceship::MoveRight() {
    position.x += 7;

    if (position.x > GetScreenWidth() - image.width - 25)
        position.x = GetScreenWidth() - image.width - 25;
}

void Spaceship::FireLaser() {

    if (GetTime() - lastFireTime >= 0.35) {
        lasers.push_back(Laser({position.x + image.width/2, position.y},-6, WHITE));

        lastFireTime = GetTime();
        PlaySound(laserSound);
    }
    
}

Rectangle Spaceship::getRect()
{

    return {position.x, position.y, float(image.width), float(image.height)};

}

void Spaceship::Reset() {
    position.x = ( GetScreenWidth() - image.width) / 2.0f;
    position.y = GetScreenHeight() - image.height - 100; // moved up due to ui

    lasers.clear();

}
