#include "game.hpp"

Game::Game(std::string title, int width, int height) : window(title, width, height) {
    aspectRatio = static_cast<float>(width) / static_cast<float>(height);
}

Game::~Game() {
    glfwDestroyWindow(window.getWindow());
    glfwTerminate();
}

void Game::setupProjection(Shader shader) {
    shader.use();

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(window.width), static_cast<float>(window.height), 0.0f, -1.0f, 1.0f);
    glUniform1i(glGetUniformLocation(shader.getID(), "image"), 0);
    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "projection"), 1, false, glm::value_ptr(projection));
}

bool Game::isRunning() {
    return !glfwWindowShouldClose(window.getWindow());
}

void Game::update() {
    float currentFrame = glfwGetTime();
    dt = currentFrame - lastFrame;
    lastFrame = currentFrame;

    mousePosition = glm::vec2(static_cast<float>(window.mouseX), static_cast<float>(window.mouseY));

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// https://www.glfw.org/docs/3.2/group__keys.html
bool Game::keyDown(int key) {
    return window.keyPressed.find(key) != window.keyPressed.end();
}

bool Game::mouseDown(int button) {
    return window.mousePressed.find(button) != window.mousePressed.end();
}

int Game::FPS() {
    return static_cast<int>(1 / dt);
}