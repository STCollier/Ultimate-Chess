#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture.hpp"
#include "shader.hpp"

class Sprite {
    public:
        std::string texturePath;
        glm::vec2 position;

        Sprite(std::string filename, Shader shader);
        ~Sprite();

        void draw(glm::vec2 position, glm::vec2 size, float rotation);
    private:
        unsigned int m_VBO, m_VAO; // TODO: perhaps use an EBO
        Texture m_texture;
        Shader m_shader;
};

#endif