#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Utility.h"
#include "DrawDemo.h"
#include "SolarSystem.h"
#include "Globals.h"



// Init Global variables
void General_Init(GLFWwindow* window)
{
    GLCall(glfwGetFramebufferSize(window, &g_WindowWidth, &g_WindowHeight));
}

int main(void)
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(2560, 1660, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error initializing GLEW" << std::endl;
        return -1;
    }

    std::cout << "GLEW initialized successfully" << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;



 


    //DrawDemo(window);
    //DrawPoint(window);
	//DrawAnimationOnePoint_Scale(window);
	//DrawTriangle(window);
    //DrawTriangleRotate(window);
	//DrawTriangleIsosceles(window);
	//DrawAnimationTrianlge(window);
    //DrawAnimationTrianlge_Move(window, glfwGetTime());

	//DrawCube(window);
    //DrawMultiCube(window);
	//DrawMultiCubeIntances(window);

	//DrawCube_And_Pyramid(window);
	//DrawPyramidWithTexture(window, true);
	//Draw3PyramidsWithTextureControls(window);

    //DrawSphere(window);
	//DrawImportedModel(window);

    //========================应用程序1- 太阳系渲染=====================================================
	General_Init(window);

    Solarinit(); // 在main函数中，在渲染循环开始前调用

    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        displaySoloar(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    SolarCleanup(); // 在程序结束前调用清理函数

    std::cout << "Loop exited. Terminating." << std::endl;
    glfwTerminate();
    return 0;
}






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
