#pragma once
#include <glad/glad.h>
#include <string>

class Texture {
public:
    Texture(const std::string& path, GLenum format = GL_RGBA);
    ~Texture();

    void bind(unsigned int unit = 0) const;
    unsigned int getID() const { return ID; }

private:
    unsigned int ID;
    int width, height, nrChannels;
};