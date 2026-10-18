#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "shaderClass.h"
#include <glm/glm.hpp>

class Cube
{
public:
    Cube(const std::string& texturePath);
    ~Cube();

    void Draw(Shader& shader, glm::mat4 model);

private:
    VAO vao;
    VBO* vbo;
    EBO* ebo;
    Texture texture;
};