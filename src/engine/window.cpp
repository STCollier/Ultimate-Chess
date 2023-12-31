#include "window.hpp"

void Window::sizeCallback(GLFWwindow *window, int width, int height) {
    (void) width, (void) height;
    Window *handler = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    handler->sizeCallback();
}

void Window::sizeCallback() {
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

void Window::mouseCallback(GLFWwindow* window, int button, int action, int mode) {
    Window *handler = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    handler->mouseCallback(button, action, mode);
}

void Window::mouseCallback(int button, int action, int mode) {
    (void) mode;

    if (action == GLFW_PRESS) {
        mousePressed.insert(button);
    } else if (action == GLFW_RELEASE) {
        mousePressed.erase(button);
    }

    glfwGetCursorPos(m_window, &mouseX, &mouseY);
}

Window::Window(std::string _title, int _width, int _height) {
    title = _title;
    width = _width;
    height = _height;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

    glfwMakeContextCurrent(m_window);

    //Load all OpenGL function pointers with Glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!\n";
        exit(1);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetFramebufferSizeCallback(m_window, sizeCallback);
    glfwSetKeyCallback(m_window, keyboardCallback);
    glfwSetMouseButtonCallback(m_window, mouseCallback);
}

GLFWwindow* Window::getWindow() {
    return m_window;
}