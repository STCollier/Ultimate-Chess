#include "sprite.hpp"

Sprite::Sprite(std::string filename, double xPos, double yPos, double scaleX, double scaleY, double rotation, glm::vec3 spriteColor, Shader shader) : m_texture(filename), m_shader(shader.vertexPath, shader.fragmentPath) {
    texturePath = filename;
    m_shader = shader;

    x = xPos;
    y = yPos;
    sx = scaleX;
    sy = scaleY;
    r = rotation;
    color = glm::vec3(spriteColor);

    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(m_VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);  
    glBindVertexArray(0);
}

/*Sprite::~Sprite() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}*/

void Sprite::draw() {
    m_shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(glm::vec2(static_cast<float>(x), static_cast<float>(y)), 0.0f));  

    glm::vec2 size(static_cast<float>(sx), static_cast<float>(sy));
    model = glm::rotate(model, glm::radians(static_cast<float>(r)), glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-size.x / 2, -size.y / 2, 0.0f)); 

    model = glm::scale(model, glm::vec3(size, 1.0f));
  
    glUniformMatrix4fv(glGetUniformLocation(m_shader.getID(), "model"), 1, false, glm::value_ptr(model));
    glUniform3f(glGetUniformLocation(m_shader.getID(), "spriteColor"), color.x/255, color.y/255, color.z/255);
  
    glActiveTexture(GL_TEXTURE0);
    m_texture.bind();

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}