#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_set>

class Window {
    public:
        std::string title;
        std::unordered_set<int> keyPressed;
        int width;
        int height;

        Window(std::string title, int width, int height);

        GLFWwindow* getWindow();
        virtual void sizeCallback(int width, int height);
        virtual void keyboardCallback(int key, int scancode, int action, int mode);
    private:
        GLFWwindow* m_window;

        static void sizeCallback(GLFWwindow *window, int width, int height);
        static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
};

#endif