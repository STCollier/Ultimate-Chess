#include <iostream>
#include "engine/game.hpp"

int main() {
    Game game("Ultimate Chess", 1920, 1080);
    Shader spriteShader("res/shaders/sprite.vert", "res/shaders/sprite.frag");
    game.setupProjection(spriteShader);

    int windowWidth = game.window.width;
    int windowHeight = game.window.height;

    Sprite pawn("res/sprites/pawn.png", windowWidth/2, windowHeight/2, 256, 256, 0, spriteShader);

    while (game.isRunning()) {
        game.update();

        pawn.draw();
        pawn.r += 100 * game.dt;

        std::cout << "FPS: " << game.FPS() << "\n";

        glfwSwapBuffers(game.window.getWindow());
        glfwSwapInterval(1);
        glfwPollEvents();
    }
}