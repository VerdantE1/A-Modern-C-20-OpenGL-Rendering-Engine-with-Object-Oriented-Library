#pragma once




void DrawPoint(GLFWwindow* window); // Draw a point in the center of the window
void DrawTriangle(GLFWwindow* window); // Draw a triangle in the center of the window
void DrawTriangleRotate(GLFWwindow* window); // Draw a triangle in the center of the window
void DrawAnimationTrianlge_Move(GLFWwindow* window); // Draw an animated triangle in the center of the window
void DrawAnimationTrianlge_Move(GLFWwindow* window, float currentTime); // Draw an animated triangle in the center of the window
void DrawAnimationOnePoint_Scale(GLFWwindow* window); // Draw an animated triangle in the center of the window
void DrawTriangleIsosceles(GLFWwindow* window); // Draw an isosceles triangle in the center of the window
void DrawDemo(GLFWwindow* window);
void DrawCube(GLFWwindow* window,bool enableAnimation = true);
void DrawMultiCube(GLFWwindow* window, bool enbaleAnimation = true);
void DrawMultiCubeIntances(GLFWwindow* window, bool enbaleAnimation = true); // Draw MultiCube using instances which can leverage the GPU performance
void DrawCube_And_Pyramid(GLFWwindow* window, bool enbaleAnimation = true);
void DrawPyramidWithTexture(GLFWwindow* window, bool enbaleAnimation); // Draw Pyramid with texture
void Draw3PyramidsWithTextureControls(GLFWwindow* window); // Draw 3 Pyramids with texture and controls