#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

typedef enum {
    PROGRAM,
    VERTEX,
    FRAGMENT
} ShaderType;

class Shader {
    public:
        std::string vertexPath;
        std::string fragmentPath;

        Shader(std::string vPath, std::string fPath);
        Shader() = default;
        
        unsigned int getID() { return m_ID; }
        void use();
    private:
        unsigned int m_ID;
        void checkCompileErrors(unsigned int shader, ShaderType type);
};

#endif