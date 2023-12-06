#include <iostream>
#include "engine/game.hpp"
#include "chess/board.hpp"

int main() {
    Game game("Ultimate Chess", 1024, 1024);
    Shader spriteShader("res/shaders/sprite.vert", "res/shaders/sprite.frag");
    game.setupProjection(spriteShader);

    [[maybe_unused]]
    int windowWidth = game.window.width;
    [[maybe_unused]]
    int windowHeight = game.window.height;

    Board board(spriteShader);

    while (game.isRunning()) {
        game.update();

        board.draw();
        board.update(game);

        glfwSwapBuffers(game.window.getWindow());
        glfwSwapInterval(1);
        glfwPollEvents();
    }
}