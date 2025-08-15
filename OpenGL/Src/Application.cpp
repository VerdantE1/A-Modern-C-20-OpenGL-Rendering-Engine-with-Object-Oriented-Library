#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Utility.h"
#include "DrawDemo.h"
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



    DrawMultiCube(window);


    //DrawDemo(window);
   

    //DrawPoint(window);
	//DrawAnimationOnePoint_Scale(window);
	//DrawTriangle(window);
    //DrawTriangleRotate(window);
	//DrawTriangleIsosceles(window);
	//DrawAnimationTrianlge(window);
    //DrawAnimationTrianlge_Move(window, glfwGetTime());

    std::cout << "Loop exited. Terminating." << std::endl;
    glfwTerminate();
    return 0;
}



