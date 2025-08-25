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
void DrawSphere(GLFWwindow*); // Draw a sphere in the center of the window
void DrawTorus(GLFWwindow*); // Draw a torus in the center of the window
void DrawImportedModel(GLFWwindow* window); // Draw an imported model in the center of the window
void DrawTorusWithLight(GLFWwindow* window); // Draw a torus with light in the center of the window

/*
 * Copyright (c) 2025 
 * Email: 2523877046@qq.com
 * Author: Baiqiang Long (Buzzlight)
 * 
 * This file is part of the ReduxGL project.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
