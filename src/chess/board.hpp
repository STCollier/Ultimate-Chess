#ifndef BOARD_H
#define BOARD_H

#include "../engine/game.hpp"
#include "piece.hpp"
#include <stdint.h>
#include <limits.h>
#include <bit>
#include <bitset>

enum BoardLocation {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8
};

class Board {
    public:
        int squares[64];
        uint64_t bitboards[12];
        uint64_t whiteBitboard, blackBitboard;
        std::vector<Piece> pieces;
        bool turn = 0; // 0 = White, 1 = Black
        bool focused = 0; // If user selects a piece on the board

        int clickedPiece;
        glm::ivec2 clickedPieceLocation;
        glm::ivec2 targetLocation;

        Board(Shader spriteShader);
        void draw();
        void update(Game& game);
        void loadFromFEN(std::string fen);
        bool makeMove();

        int pieceAt(int location) { return squares[location]; }
        int pieceType(int location) { return squares[location] & 0b111; }
        int pieceColor(int location) { return (squares[location] >> 3) << 3; }

        void printBitboard(uint64_t b);
        void setBit(uint64_t &b, int i) { b |= (1ULL << i); }
        int getBit(uint64_t b, int i) { return b & (1ULL << i); }
        void clearBit(uint64_t &b, int i) { b &= ~(1ULL << i); }
        int lsb(uint64_t b) { return std::__countr_zero(b); };
        int popLSB(uint64_t &b);
    private:
        Sprite m_boardSprites[64];

        glm::vec3 m_lightColor = glm::vec3(255, 242, 216);
        glm::vec3 m_darkColor = glm::vec3(176, 146, 106);
};

#endif