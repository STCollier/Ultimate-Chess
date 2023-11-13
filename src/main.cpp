#include <iostream>
#include "engine/game.hpp"

int main() {
    Game game("Ultimate Chess", 1920, 1080);

    while (game.isRunning()) {

        game.update();
    }
}