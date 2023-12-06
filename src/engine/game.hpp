#ifndef GAME_H
#define GAME_H

#include "stb_image/stb_image.h"

#include <iostream>
#include <unordered_map>
#include <map>
#include <ctype.h>
#include <vector>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window.hpp"
#include "shader.hpp"
#include "sprite.hpp"
#include "shader.hpp"

#define LEFT_CLICK GLFW_MOUSE_BUTTON_LEFT
#define RIGHT_CLICK GLFW_MOUSE_BUTTON_RIGHT
#define MIDDLE_CLICK GLFW_MOUSE_BUTTON_MIDDLE

class Game {
    public:
        Window window;
        std::unordered_set<int> keyPressed;
        std::unordered_set<int> mousePressed;
        glm::vec2 mousePosition;
        float dt;
        float lastFrame;
        float aspectRatio;
    
        Game(std::string title, int width, int height);
        ~Game();

        void setupProjection(Shader shader);
        bool isRunning();
        void update();
        bool keyDown(int key);
        bool mouseDown(int button);
        int FPS();
};

#endif