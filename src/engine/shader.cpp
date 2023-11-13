#include "shader.hpp"

// Posssible Optimization
/*
static std::string LoadFileToString(std::string_view path) {
    std::ifstream file{std::string(path), std::ios::binary};

    if (!file.is_open())
        throw std::runtime_error(std::format("Could not open file {}", path));


    std::string contents;

    file.seekg(0, std::ios::end);
    contents.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&contents[0], contents.size());

    return contents;
}
*/

Shader::Shader(std::string vPath, std::string fPath) {
    vertexPath = vPath;
    fragmentPath = fPath;

    std::ifstream vertexFile(vertexPath);
    std::ifstream fragmentFile(fragmentPath);

    std::stringstream vertexSource;
    vertexSource << vertexFile.rdbuf();

    std::stringstream fragmentSource;
    fragmentSource << fragmentFile.rdbuf();

    std::string f = fragmentSource.str();
    const char* fResult = f.c_str();

    std::string v = vertexSource.str();
    const char* vResult = v.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vResult, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, VERTEX);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fResult, NULL);
    glCompileShader(fragmentShader);  
    checkCompileErrors(fragmentShader, FRAGMENT);

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShader);
    glAttachShader(m_ID, fragmentShader);
    glLinkProgram(m_ID);
    checkCompileErrors(m_ID, PROGRAM);

    //Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::checkCompileErrors(unsigned int shader, ShaderType type) {
    int success;
    char infoLog[1024];
    if (type != PROGRAM)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}

void Shader::use() {
    glUseProgram(m_ID);
}