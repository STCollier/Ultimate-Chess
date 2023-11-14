#ifndef BOARD_H
#define BOARD_H

#include "../engine/shader.hpp"
#include "../engine/sprite.hpp"

class Board {
    public:
        int square[64];

        Board(Shader spriteShader);
        void draw();
    private:
        Sprite m_sprites[64];
};

#endif