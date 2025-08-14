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
void setupVertices(void) {    // 36 �����㣬12�������Σ�����˷�����ԭ�㴦��2��2��2������ 
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
    // ������ɫ������
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f; // ��ʼ�������λ��
    cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f; // ��ʼ��������λ��
    setupVertices(); // ���ö�������
}



// ��ʾ����
void display(GLFWwindow* window, double currentTime) {
    glClear(GL_DEPTH_BUFFER_BIT); // �����Ȼ�����

    GLCall(glUseProgram(renderingProgram)); // ʹ����ɫ������

    // ��ȡ uniform ������λ��
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

    // ��ȡ���ڳߴ粢�����߱�
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // ����ͶӰ����

    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ)); // ������ͼ����
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ)); // ����ģ�;���
    mvMat = vMat * mMat; // ����ģ��-��ͼ����

    // �����󴫵ݵ���ɫ��
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // �� VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0); // ���ö�������ָ��
    glEnableVertexAttribArray(0); // ���ö�������

    glEnable(GL_DEPTH_TEST); // ������Ȳ���
    glDepthFunc(GL_LEQUAL); // ������Ȳ��Ժ���

    glDrawArrays(GL_TRIANGLES, 0, 36); // ����������
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
        display(window, glfwGetTime()); // ������ʾ����

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



