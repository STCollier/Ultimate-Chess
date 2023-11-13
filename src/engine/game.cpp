#include "game.hpp"

Game::Game(std::string title, int width, int height) : window(title, width, height) {
    Shader spriteShader("res/sprite.vert", "res/sprite.frag");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(window.width), static_cast<float>(window.height), 0.0f, -1.0f, 1.0f);
    glUniform1i(glGetUniformLocation(spriteShader.getID(), "image"), 0);
    glUniformMatrix4fv(glGetUniformLocation(spriteShader.getID(), "projection"), 1, false, glm::value_ptr(projection));

    Sprite pawn("res/pawn.png", spriteShader);
}

Game::~Game() {
    glfwDestroyWindow(window.getWindow());
    glfwTerminate();
}

bool Game::isRunning() {
    return !glfwWindowShouldClose(window.getWindow());
}

void Game::update() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float currentFrame = glfwGetTime();
    dt = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glfwSwapBuffers(window.getWindow());
    glfwPollEvents();
}

// https://www.glfw.org/docs/3.2/group__keys.html
bool Game::keyDown(int key) {
    return window.keyPressed.find(key) != window.keyPressed.end();
}

int Game::FPS() {
    return static_cast<int>(1 / dt);
}