#define STB_IMAGE_IMPLEMENTATION

#include "texture.hpp"

Texture::Texture(std::string textureFilename) {
    textureFilename = filename;

    glGenTextures(1, &ID);

    data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    if (data) {
        GLenum format;

        switch (channels) {
            case 1: 
                format = GL_RED;
                break;
            case 2:
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
        }

        glBindTexture(GL_TEXTURE_2D, ID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cerr << "Could not find texture file: " << textureFilename << "\n";
        exit(1);
    }
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, ID);
}

Texture::~Texture() {
    glDeleteTextures(1, &ID);
}