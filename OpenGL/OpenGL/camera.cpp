#include "Camera.h"
#include "shaderClass.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 front)
{
	// Initialize camera parameters
    Position = position;
    Up = up;
    Front = front;
	//speed of the camera movement
    Speed = 2.5f;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(GLFWwindow* window, float deltaTime)
{
    float velocity = Speed * deltaTime;
	//front and back movement
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            Position += velocity * Front;

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            Position -= velocity * Front;
	//we create a vector who indicates the right direction of the camera
    glm::vec3 right = glm::normalize(glm::cross(Front, Up));
	//left and right movement
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            Position -= velocity * right;

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            Position += velocity * right;
	//up and down movement
        //we move across y axis
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
            Position += velocity * Up;

        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
            Position -= velocity * Up;
}
//this function calculates the view and projection matrices and sends them to the shader
void Camera::Matrix(float FOVdeg, float aspectRatio, float nearPlane, float farPlane,
    Shader& shader, const char* uniform)
{
	//view matrix -world to camera space
    glm::mat4 view = glm::mat4(1.0f);
	//projection matrix -camera space to clip space
    glm::mat4 projection = glm::mat4(1.0f);
	//we calculate the view and projection matrices
    view = glm::lookAt(Position, Position + Front, Up);
	//we create the perspective projection matrix using the FOV, aspect ratio, near and far planes
    projection = glm::perspective(glm::radians(FOVdeg), aspectRatio, nearPlane, farPlane);
    
    glm::mat4 vp = projection * view;
	//we send the view and projection matrices to the gpu
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(vp));
}