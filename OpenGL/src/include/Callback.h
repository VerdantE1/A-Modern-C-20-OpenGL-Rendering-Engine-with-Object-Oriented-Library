#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Declare aspect and pMat as extern if they are defined elsewhere
extern float aspect;
extern glm::mat4 pMat;

void window_reshape_callback(GLFWwindow* window, int newWidth, int newHeight) {
    aspect = (float)newWidth / (float)newHeight;    // Callback provides new width and height
    glViewport(0, 0, newWidth, newHeight);          // Set the screen area related to framebuffer
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}