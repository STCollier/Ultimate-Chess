#include <iostream>
#include "engine/game.hpp"
#include "chess/board.hpp"

int main() {
    Game game("Ultimate Chess", 1920, 1080);
    Shader spriteShader("res/shaders/sprite.vert", "res/shaders/sprite.frag");
    game.setupProjection(spriteShader);

    int windowWidth = game.window.width;
    int windowHeight = game.window.height;

    //Board board(spriteShader);
    Sprite pawn;
    pawn = {"res/sprites/pawn.png", windowWidth/2, windowHeight/2, 256, 256, 0, spriteShader};



    while (game.isRunning()) {
        game.update();

        //board.draw();
        pawn.draw();

        glfwSwapBuffers(game.window.getWindow());
        glfwSwapInterval(1);
        glfwPollEvents();
    }
}