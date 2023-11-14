#include "board.hpp"

Board::Board(Shader spriteShader) : m_sprites{} {
    for (int file = 0; file < 8; file++) { // columns
        for (int rank = 0; rank < 8; rank++) { // rows
            m_sprites[(rank * 8) + file] = {"res/sprites/pawn.png", 200, 200, 128, 128, 0, spriteShader};
        }
    }
}

void Board::draw() {
    for (int i = 0; i < 64; i++) m_sprites[i].draw();
}