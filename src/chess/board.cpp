#include "board.hpp"

static inline const std::string startingFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

Board::Board(Shader spriteShader) : m_boardSprites{}, m_pieceSprites{} {
    for (int file = 0; file < 8; file++) { // columns
        for (int rank = 0; rank < 8; rank++) { // rows
            bool lightSquare = (file + rank) % 2;

            glm::vec3 squareColor = lightSquare ? m_lightColor : m_darkColor;

            m_boardSprites[(rank * 8) + file] = {"res/sprites/square.png", static_cast<double>(rank*128 + 64), static_cast<double>(file*128 + 64), 128, 128, 0, squareColor, spriteShader};
        }
    }

    loadFromFEN(startingFen);

    for (int file = 0; file < 8; file++) { // columns
        for (int rank = 0; rank < 8; rank++) { // rows
            std::string color = "", type = "";
            int index = (rank * 8) + file;
            if (pieceColor(index) == WHITE) {
                color = "white";

                switch (pieceType(index)) {
                    case PAWN:
                        type = "pawn";
                        break;
                    case KNIGHT:
                        type = "knight";
                        break;
                    case BISHOP:
                        type = "bishop";
                        break;
                    case ROOK:
                        type = "rook";
                        break;
                    case QUEEN:
                        type = "queen";
                        break;
                    case KING:
                        type = "king";
                        break;
                }
            } else if (pieceColor(index) == BLACK) {
                color = "black";

                switch (pieceType(index)) {
                    case PAWN:
                        type = "pawn";
                        break;
                    case KNIGHT:
                        type = "knight";
                        break;
                    case BISHOP:
                        type = "bishop";
                        break;
                    case ROOK:
                        type = "rook";
                        break;
                    case QUEEN:
                        type = "queen";
                        break;
                    case KING:
                        type = "king";
                        break;
                }
            }

            //std::cout << "res/sprites/" + type + "_" + color + ".png\n"; 
            if (type != "" && color != "") m_pieceSprites.push_back({"res/sprites/" + type + "_" + color + ".png", static_cast<double>(file*128 + 64), static_cast<double>(1024-128 - rank*128 + 64), 128, 128, 0, glm::vec3(255, 255, 255), spriteShader});
        }
    }
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

                squares[(rank * 8) + file] = pColor | pType;

                file++;
            }
        }
    }
}

void Board::draw() {
    for (int i = 0; i < 64; i++) {
        m_boardSprites[i].draw();
    }

    for (auto piece = m_pieceSprites.begin(); piece != m_pieceSprites.end(); piece++) {
        piece->draw();
    }
}

void Board::update(Game& game) {
    if (game.mouseDown(LEFT_CLICK)) {
        glm::ivec2 clicked =  glm::ivec2(static_cast<int>(game.mousePosition.x / 128), static_cast<int>(game.mousePosition.y / 128));

        for (auto piece = m_pieceSprites.begin(); piece != m_pieceSprites.end(); piece++) {
            if (clicked.x * 128 + 64 == static_cast<int>(piece->x) && clicked.y * 128 + 64 == static_cast<int>(piece->y) && !focused) {
                focused = true;
                clickedPieceLocation = clicked;

                int squareIdx = 8 * clickedPieceLocation.x + clickedPieceLocation.y;
                m_boardSprites[squareIdx].color = glm::vec3(0, 255, 0);

                std::cout << pieceType(squareIdx) << "\n";
            }
        }

        if (focused && (clickedPieceLocation.x != clicked.x || clickedPieceLocation.y != clicked.y)) {
            targetPieceLocation = clicked;

            int squareIdx = 8 * clickedPieceLocation.x + clickedPieceLocation.y;
            m_boardSprites[squareIdx].color = (clickedPieceLocation.x + clickedPieceLocation.y) % 2 ? m_lightColor : m_darkColor;
            focused = false;
        }
    }
}   