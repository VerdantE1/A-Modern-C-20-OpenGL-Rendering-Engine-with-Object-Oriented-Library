#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void DrawPoint(GLFWwindow* window); // Draw a point in the center of the window
void DrawTriangle(GLFWwindow* window); // Draw a triangle in the center of the window
void DrawAnimationTrianlge_Move(GLFWwindow* window); // Draw an animated triangle in the center of the window
void DrawAnimationTrianlge_Move(GLFWwindow* window, float currentTime); // Draw an animated triangle in the center of the window
void DrawAnimationOnePoint_Scale(GLFWwindow* window); // Draw an animated triangle in the center of the window
void DrawTriangleIsosceles(GLFWwindow* window); // Draw an isosceles triangle in the center of the window
void DrawDemo(GLFWwindow* window);
void DrawCube(GLFWwindow* window);
