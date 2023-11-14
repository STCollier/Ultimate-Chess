#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "stb_image/stb_image.h"
#include <iostream>

class Texture {
    public:
        std::string filename;
        int width;
        int height;
        int channels;
        unsigned char* data; // Actual image data
        unsigned int ID;

        Texture(std::string textureFilename);
        Texture() = default;
        ~Texture();

        void bind();
};

#endif  