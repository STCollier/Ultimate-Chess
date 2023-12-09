#include "piece.hpp"

Piece::Piece(int t, glm::ivec2 pos, Shader shader) : sprite{} {
    position = pos;
    type = t;

    switch (t) {
        case Pawn::White:
            m_texturePath = "res/sprites/pawn_white.png";
            break;
        case Knight::White:
            m_texturePath = "res/sprites/knight_white.png";
            break;
        case Bishop::White:
            m_texturePath = "res/sprites/bishop_white.png";
            break;
        case Rook::White:
            m_texturePath = "res/sprites/rook_white.png";
            break;
        case Queen::White:
            m_texturePath = "res/sprites/queen_white.png";
            break;
        case King::White:
            m_texturePath = "res/sprites/king_white.png";
            break;
        case Pawn::Black:
            m_texturePath = "res/sprites/pawn_black.png";
            break;
        case Knight::Black:
            m_texturePath = "res/sprites/knight_black.png";
            break;
        case Bishop::Black:
            m_texturePath = "res/sprites/bishop_black.png";
            break;
        case Rook::Black:
            m_texturePath = "res/sprites/rook_black.png";
            break;
        case Queen::Black:
            m_texturePath = "res/sprites/queen_black.png";
            break;
        case King::Black:
            m_texturePath = "res/sprites/king_black.png";
            break;
    }

    sprite = {m_texturePath, static_cast<double>(position.x*128 + 64), static_cast<double>(1024-128 - position.y*128 + 64), 128, 128, 0, glm::vec3(255, 255, 255), shader};
}

void Piece::setPosition(glm::ivec2 location) {
    position = location;

    sprite.x = posToCoord().x;
    sprite.y = posToCoord().y;
}

bool Piece::comparePosition(glm::ivec2 position) {
    return position.x * 128 + 64 == static_cast<int>(sprite.x) && position.y * 128 + 64 == static_cast<int>(sprite.y);
}

bool Piece::getColor() {
    if (type == Pawn::White || type == Knight::White || type == Bishop::White || type == Rook::White || type == Queen::White || type == King::White) {
        return false; // 0 (White)
    } else {
        return true; // 1 (Black)
    }
}