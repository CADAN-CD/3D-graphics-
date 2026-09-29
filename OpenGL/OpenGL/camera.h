#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader;
class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;

    float Speed;

	//initial position of the camera begining at origin 
	    // Constructor 
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f));

    glm::mat4 GetViewMatrix();
	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(GLFWwindow* window, float deltaTime);

    void Matrix(float FOVdeg, float aspectRatio, float nearPlane, float farPlane,
        Shader& shader, const char* uniform);
};
