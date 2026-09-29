#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../OpenGL/shaderClass.h"
#include "../OpenGL/VAO.h"
#include "../OpenGL/VBO.h"
#include "../OpenGL/EBO.h"

//textures
#include "../OpenGL/stb_image.h"
#include "../OpenGL/Texture.h"
//camera movement
#include "../OpenGL/camera.h"

int main()
{
	// Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	GLFWwindow* window = glfwCreateWindow(800, 800, "IndicesOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	
	gladLoadGL();
	glViewport(0, 0, 800, 800);
	glEnable(GL_DEPTH_TEST);

	// Vertices coordinates
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

	Shader shaderProgram("default.vert", "default.frag");
	shaderProgram.Activate();
	//we create the VAO, VBO and EBO objects and link them together
	VAO VAO1;
	
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	//we link the attributes of the location and the UV coordinates to the VAO
	VAO1.LinkVBO(VBO1, 0);   // position
	VAO1.LinkVBO(VBO1, 1);   // UV
	EBO1.Bind();

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	
	
		//TEXTURES
	Texture cubeTexture("../textures/texture.jpg");
	//modelLoc will store the location of the model matrix in the shader
	GLuint modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
	//tex0Loc will store the location of the texture in the shader
	GLuint tex0Loc = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0Loc, 0);
	

		//CAMERA
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float lastFrame = 0.0f;
	float deltaTime = 0.0f;


	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera.ProcessKeyboard(window, deltaTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		camera.Matrix(45.0f, 800.0f / 800.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0, 1, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		VAO1.Bind();
		cubeTexture.bind(0);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	

	VAO1.Delete();
	VBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}