#ifndef GAME_H
#define GAME_H

#include "stb_image/stb_image.h"

#include <iostream>
#include <unordered_map>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window.hpp"
#include "shader.hpp"
#include "sprite.hpp"
#include "shader.hpp"

class Game {
    public:
        Window window;
        std::unordered_set<int> keyPressed;
        float dt;
        float lastFrame;
        float aspectRatio;
    
        Game(std::string title, int width, int height);
        ~Game();

        void setupProjection(Shader shader);
        bool isRunning();
        void update();
        bool keyDown(int key);
        int FPS();
};

#endif