#ifndef PIECE_H
#define PIECE_H

#include "../engine/game.hpp"

enum PieceType {
    PAWN = 0,
    KNIGHT = 1,
    BISHOP = 2,
    ROOK = 3,
    QUEEN = 4,
    KING = 5,
};

enum PieceColor {
    WHITE = 0,
    BLACK = 6
};

namespace Pawn {
    const int White = 0;
    const int Black = 6;
};

namespace Knight {
    const int White = 1;
    const int Black = 7;
};

namespace Bishop {
    const int White = 2;
    const int Black = 8;
};

namespace Rook {
    const int White = 3;
    const int Black = 9;
};

namespace Queen {
    const int White = 4;
    const int Black = 10;
};

namespace King {
    const int White = 5;
    const int Black = 11;
};

class Piece {
    public:
        int type;
        glm::ivec2 position;
        Sprite sprite;

        Piece(int t, glm::ivec2 pos, Shader shader);
        Piece() = default;

        bool getColor();
        bool comparePosition(glm::ivec2 position);
        void setPosition(glm::ivec2 location);

    private:
        std::string m_texturePath;

        // Piece position to screen space
        glm::dvec2 posToCoord() { return glm::dvec2(static_cast<double>(position.x*128 + 64), static_cast<double>(position.y*128 + 64)); } 
};

#endif