#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AllShaperTypes.h"
#include "Shader.h"
#include "Renderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Utility.h"
#include "Ds/TransformStack.h"
#include "Globals.h"

class GLFWwindow;

TransformStack transformStk;

void displaySoloar(GLFWwindow* window, double currentTime)
{
    //=========================��ʼ��========================================
    Camera camera(
        glm::vec3(0, 0, 10),  // position
        glm::vec3(0, 0, 0),   // target
        glm::vec3(0, 1, 0),   // up
        70.0f, (float)g_WindowWidth / (float)g_WindowHeight, 0.1f, 100.0f
    );

    Shader shader("res/shaders/SoloarSystem.shader");
    Renderer renderer;
    Cube Earth, Moon;
    Pyramid Sun;

    renderer.SetDepthTest(true).SetPolygonMode(false).SetCullFace(true);
    renderer.Clear();

    //==========================���ñ任����========================================

    //��ȡͶӰ����P
    Transform porjectionTransform = camera.GetProjectionMatrix();
    transformStk.Push(porjectionTransform);

    //��ȡ��ͼ����V
    Transform viewTransform = camera.GetViewMatrix();
    transformStk.Push(viewTransform);

    Transform earthTransformPos, moonTransformPos, sunTransformPos;
    Transform earthTransformRotate, moonTransformRotate, sunTransformRotate;

    //----------------------------̫��------------------------------------------
    sunTransformPos.setPosition(0.0f, 0.0f, 0.0f);
    transformStk.Push(sunTransformPos);

    sunTransformRotate.setRotation((float)currentTime, 0, 0);
    transformStk.Push(sunTransformRotate);

    shader.SetUniformMat4fv("mvp_matrix", transformStk.Top().getMatrix());
    renderer.Draw(Sun, shader);
    transformStk.Pop();

    //----------------------------����------------------------------------------
    earthTransformPos.setPosition(sin((float)currentTime) * 8.0, 0.0f, cos((float)currentTime) * 4.0);
    transformStk.Push(earthTransformPos);

    earthTransformRotate.setRotation(0.0f, (float)currentTime, 0.0f);
    earthTransformRotate.setScale(0.5f, 0.5f, 0.5f);
    transformStk.Push(earthTransformRotate);

    shader.SetUniformMat4fv("mvp_matrix", transformStk.Top().getMatrix());
    renderer.Draw(Earth, shader);
    transformStk.Pop();

    //----------------------------����------------------------------------------
    moonTransformPos.setPosition(0, sin((float)currentTime) * 1.0, cos((float)currentTime) * 1.0f);
    transformStk.Push(moonTransformPos);

    moonTransformRotate.setRotation(0.0f, (float)currentTime, 0.0f);
    moonTransformRotate.setScale(0.2f, 0.2f, 0.2f);
    transformStk.Push(moonTransformRotate);

    shader.SetUniformMat4fv("mvp_matrix", transformStk.Top().getMatrix());
    renderer.Draw(Moon, shader);

    transformStk.Clear(); // ��ձ任ջ��׼����һ������ı任
}