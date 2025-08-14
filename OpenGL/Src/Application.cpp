#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Utility.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "DrawDemo.h"

float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
#define numVAOs 1 
#define numVBOs 2 



GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];


GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;

#include "Utils.h"
void setupVertices(void) {    // 36 个顶点，12个三角形，组成了放置在原点处的2×2×2立方体 
    float vertexPositions[108] = {
       -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
       1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
       1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
       1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
       1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
       -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
       -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
       -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
       -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
       1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
       -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
       1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
    };
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}


void init(GLFWwindow* window) {
    renderingProgram = Utils::createShaderProgram("res/shader/vertShader.shader", "res/shader/fragShader.shader");
    // 创建着色器程序
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f; // 初始化摄像机位置
    cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f; // 初始化立方体位置
    setupVertices(); // 设置顶点数据
}



// 显示函数
void display(GLFWwindow* window, double currentTime) {
    glClear(GL_DEPTH_BUFFER_BIT); // 清除深度缓冲区

    GLCall(glUseProgram(renderingProgram)); // 使用着色器程序

    // 获取 uniform 变量的位置
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

    // 获取窗口尺寸并计算宽高比
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 设置投影矩阵

    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ)); // 设置视图矩阵
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ)); // 设置模型矩阵
    mvMat = vMat * mMat; // 计算模型-视图矩阵

    // 将矩阵传递到着色器
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // 绑定 VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0); // 设置顶点属性指针
    glEnableVertexAttribArray(0); // 启用顶点属性

    glEnable(GL_DEPTH_TEST); // 启用深度测试
    glDepthFunc(GL_LEQUAL); // 设置深度测试函数

    glDrawArrays(GL_TRIANGLES, 0, 36); // 绘制立方体
}


int main(void)
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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


    while (!glfwWindowShouldClose(window))
    {
        display(window, glfwGetTime()); // 调用显示函数

        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

    //DrawDemo(window);
    //DrawCube(window);

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



