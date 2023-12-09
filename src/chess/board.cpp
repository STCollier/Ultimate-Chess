#include "board.hpp"

static inline const std::string startingFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

Board::Board(Shader spriteShader) : pieces{}, m_boardSprites{} {
    for (int file = 0; file < 8; file++) { // columns
        for (int rank = 0; rank < 8; rank++) { // rows
            bool lightSquare = (file + rank) % 2;

            glm::vec3 squareColor = lightSquare ? m_lightColor : m_darkColor;

            m_boardSprites[(rank * 8) + file] = {"res/sprites/square.png", static_cast<double>(rank*128 + 64), static_cast<double>(file*128 + 64), 128, 128, 0, squareColor, spriteShader};
        }
    }

    loadFromFEN(startingFen);

    for (int p = 0; p < 12; p++) {
        auto bb = bitboards[p];

        while (bb) {
            const auto sq = popLSB(bb);
            int file = sq % 8;
            int rank = sq / 8;
            
            Piece _piece{p, glm::vec2(file, rank), spriteShader};

            pieces.push_back(_piece);
        }
    }

    whiteBitboard = bitboards[Pawn::White] | bitboards[Knight::White] | bitboards[Bishop::White] | bitboards[Rook::White] | bitboards[Queen::White] | bitboards[King::White];
    blackBitboard = bitboards[Pawn::Black] | bitboards[Knight::Black] | bitboards[Bishop::Black] | bitboards[Rook::Black] | bitboards[Queen::Black] | bitboards[King::Black];
}

void Board::loadFromFEN(std::string fen) {
    std::map<char, int> pieceTypeFromSymbol;
    pieceTypeFromSymbol['p'] = PAWN;
    pieceTypeFromSymbol['n'] = KNIGHT;
    pieceTypeFromSymbol['b'] = BISHOP;
    pieceTypeFromSymbol['r'] = ROOK;
    pieceTypeFromSymbol['k'] = QUEEN;
    pieceTypeFromSymbol['q'] = KING;

    int file = 0;
    int rank = 7;

    for (char symbol : fen) {
        if (symbol == '/') {
            file = 0;
            rank--;
        } else {
            if (isdigit(symbol)) {
                file += std::stoi(std::string{symbol});
            } else {
                int pColor = isupper(symbol) ? WHITE : BLACK;
                int pType = pieceTypeFromSymbol[tolower(symbol)];
                int idx = (rank * 8) + file;

                setBit(bitboards[pType + pColor], idx);

                file++;
            }
        }
    }
}

void Board::draw() {
    for (int i = 0; i < 64; i++) {
        m_boardSprites[i].draw();
    }

    for (auto piece = pieces.begin(); piece != pieces.end(); piece++) {
        piece->sprite.draw();
    }
}

void Board::update(Game& game) {
    if (game.mouseDown(LEFT_CLICK)) {
        glm::ivec2 clicked =  glm::ivec2(static_cast<int>(game.mousePosition.x / 128), static_cast<int>(game.mousePosition.y / 128));

        for (auto piece = pieces.begin(); piece != pieces.end(); piece++) {
            if (!focused && (clicked.x * 128 + 64 == static_cast<int>(piece->sprite.x) && clicked.y * 128 + 64 == static_cast<int>(piece->sprite.y))) {
                if (piece->getColor() == turn) {
                    focused = true;
                    clickedPieceLocation = clicked;
                    clickedPiece = std::distance(pieces.begin(), piece);

                    int squareIdx = 8 * clickedPieceLocation.x + clickedPieceLocation.y;
                    m_boardSprites[squareIdx].color = glm::vec3(0, 255, 0);
                }
            }
        }

        if (focused && (clickedPieceLocation.x != clicked.x || clickedPieceLocation.y != clicked.y)) {
            targetLocation = clicked;
            int squareIdx = 8 * clickedPieceLocation.x + clickedPieceLocation.y;

            if (makeMove()) {
                m_boardSprites[squareIdx].color = (clickedPieceLocation.x + clickedPieceLocation.y) % 2 ? m_lightColor : m_darkColor;

                focused = false;
            }
        }
    }
}

bool Board::makeMove() {
    Piece piece = pieces[clickedPiece];
    int startSquare = 8 * piece.position.x + piece.position.y;
    int targetSquare = 8 * targetLocation.x + targetLocation.y;


    for (auto p = pieces.begin(); p != pieces.end(); p++) {
        if (p->comparePosition(targetLocation)) {
            if (p->getColor() != turn) {
                pieces.erase(pieces.begin() + std::distance(pieces.begin(), p));
                clearBit(bitboards[p->type], targetLocation);
            }
            else return false;
        }
    }

    clearBit(bitboards[piece.type], startSquare);
    setBit(bitboards[piece.type], targetSquare);

    pieces[clickedPiece].setPosition(targetLocation);

    turn = !turn;
    return true;
}

void Board::printBitboard(uint64_t b) {
    uint64_t i; 
    i = 1UL << (sizeof(b) * CHAR_BIT - 1);
    while(i > 0) {
        b & i ? printf("1") : printf("0"); 
        i >>= 1;
    }
    puts("");
}

int Board::popLSB(uint64_t &b) {
    int i = lsb(b);
    b &= b - 1;
    return i;
}