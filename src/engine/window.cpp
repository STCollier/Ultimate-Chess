#include "window.hpp"

void Window::sizeCallback(GLFWwindow *window, int width, int height) {
    Window *handler = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    handler->sizeCallback(width, height);
}

void Window::sizeCallback(int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    Window *handler = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    handler->keyboardCallback(key, scancode, action, mode);
}

void Window::keyboardCallback(int key, int scancode, int action, int mode) {
    (void) scancode, (void) action, (void) mode;

    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window, 1);
    }

    if (action == GLFW_PRESS) {
        keyPressed.insert(key);
    } else if (action == GLFW_RELEASE) {
        keyPressed.erase(key);
    }
}

Window::Window(std::string title, int width, int height) {
    title = title;
    width = width;
    height = height;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    glfwSetWindowUserPointer(m_window, this);

    if (m_window == NULL) {
        std::cerr << "Failed to create GLFW window!\n";
        glfwTerminate();
        exit(1);
    }

    glfwSwapInterval(1);
    glfwMakeContextCurrent(m_window);

    //Load all OpenGL function pointers with Glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!\n";
        exit(1);
    }

    glfwSetFramebufferSizeCallback(m_window, sizeCallback);
    glfwSetKeyCallback(m_window, keyboardCallback);
}

GLFWwindow* Window::getWindow() {
    return m_window;
}