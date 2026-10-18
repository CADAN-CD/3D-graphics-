#include "Cube.h"
#include <glm/gtc/type_ptr.hpp>
Cube::Cube(const std::string& texturePath) : texture(texturePath)
{
	float vertices[] = {
		// ---- front  ----
		-0.5f,-0.5f, 0.5f,  0.0f, 0.0f,
		 0.5f,-0.5f, 0.5f,  1.0f, 0.0f,
		 0.5f, 0.5f, 0.5f,  1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f,  0.0f, 1.0f,

		// ---- backwards  ----
		 0.5f,-0.5f,-0.5f,  0.0f, 0.0f,
		-0.5f,-0.5f,-0.5f,  1.0f, 0.0f,
		-0.5f, 0.5f,-0.5f,  1.0f, 1.0f,
		 0.5f, 0.5f,-0.5f,  0.0f, 1.0f,

		 // ---- left ----
		 -0.5f,-0.5f,-0.5f,  0.0f, 0.0f,
		 -0.5f,-0.5f, 0.5f,  1.0f, 0.0f,
		 -0.5f, 0.5f, 0.5f,  1.0f, 1.0f,
		 -0.5f, 0.5f,-0.5f,  0.0f, 1.0f,

		 // ---- right  ----
		  0.5f,-0.5f, 0.5f,  0.0f, 0.0f,
		  0.5f,-0.5f,-0.5f,  1.0f, 0.0f,
		  0.5f, 0.5f,-0.5f,  1.0f, 1.0f,
		  0.5f, 0.5f, 0.5f,  0.0f, 1.0f,

		  // ---- down ----
		  -0.5f,-0.5f,-0.5f,  0.0f, 0.0f,
		   0.5f,-0.5f,-0.5f,  1.0f, 0.0f,
		   0.5f,-0.5f, 0.5f,  1.0f, 1.0f,
		  -0.5f,-0.5f, 0.5f,  0.0f, 1.0f,

		  // ---- up ----
		  -0.5f, 0.5f, 0.5f,  0.0f, 0.0f,
		   0.5f, 0.5f, 0.5f,  1.0f, 0.0f,
		   0.5f, 0.5f,-0.5f,  1.0f, 1.0f,
		  -0.5f, 0.5f,-0.5f,  0.0f, 1.0f,
	};
	unsigned int indices[] = {
		0,1,2,   2,3,0,      // front
		4,5,6,   6,7,4,      // backwards
		8,9,10,  10,11,8,    // left
		12,13,14,14,15,12,   // right
		16,17,18,18,19,16,   // down
		20,21,22,22,23,20    // up	
	};
	vao.Bind();
	vbo = new VBO(vertices, sizeof(vertices));
	ebo = new EBO(indices, sizeof(indices));

	vao.LinkVBO(*vbo, 0);
	vao.LinkVBO(*vbo, 1);
	ebo->Bind();

	vao.Unbind();
	vbo->Unbind();
	ebo->Unbind();
}
Cube::~Cube()
{
	delete vbo;
	delete ebo;
}

void Cube::Draw(Shader& shader, glm::mat4 model)
{
	shader.Activate();
	texture.bind(0);
	GLuint modelLoc = glGetUniformLocation(shader.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	vao.Bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}