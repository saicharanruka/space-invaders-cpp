#ifndef BLOCK_H
#define BLOCK_H

#include <raylib.h>

class Block {

    public:
        Block(Vector2 position);
        void Draw();
        Rectangle getRect();
    private:
        Vector2 position;
};




#endif 