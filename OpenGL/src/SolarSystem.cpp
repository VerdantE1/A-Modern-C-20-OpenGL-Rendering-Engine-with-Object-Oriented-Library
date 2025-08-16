#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AllShaperTypes.h"
#include "Shader.h"
#include "Renderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Utility.h"
#include "Texture.h"  // �������ͷ�ļ�
#include "Ds/TransformStack.h"
#include "Globals.h"

class GLFWwindow;

// ȫ�ֱ�������
TransformStack transformStk;

// ȫ��������� - �������������������б���
Texture* sunTexture = nullptr;
Texture* earthTexture = nullptr;
Texture* moonTexture = nullptr;

// ȫ����ɫ������״���� - ����ÿ֡���´���
Shader* solarShader = nullptr;
Pyramid* Sun = nullptr;
Pyramid* Earth = nullptr;
Pyramid* Moon = nullptr;

void Solarinit()
{
    // ֻ��ʼ��һ���������
    if (sunTexture == nullptr) {
        sunTexture = new Texture("res/textures/2k_sun.jpg",
            TextureFilterMode::LINEAR,
            TextureFilterMode::LINEAR_MIPMAP_LINEAR,
            TextureWrapMode::REPEAT,
            TextureWrapMode::REPEAT,
            true,  // ����mipmap
            true); // ��ֱ��ת

        earthTexture = new Texture("res/textures/2k_earth_clouds.jpg",
            TextureFilterMode::LINEAR,
            TextureFilterMode::LINEAR_MIPMAP_LINEAR,
            TextureWrapMode::REPEAT,
            TextureWrapMode::REPEAT,
            true,  // ����mipmap
            true); // ��ֱ��ת

        moonTexture = new Texture("res/textures/2k_mercury.jpg",
            TextureFilterMode::LINEAR,
            TextureFilterMode::LINEAR_MIPMAP_LINEAR,
            TextureWrapMode::REPEAT,
            TextureWrapMode::REPEAT,
            true,  // ����mipmap
            true); // ��ֱ��ת

        // ��ʼ����ɫ��������ÿ֡���¼��أ�
        solarShader = new Shader("res/shaders/SoloarSystem.shader");

        // ��ʼ����״����
        Sun = new Pyramid();
        Earth = new Pyramid();
        Moon = new Pyramid();

        // ��ӡ��ʼ����Ϣ
        std::cout << "Solar System Initialized:" << std::endl;
        std::cout << "Sun texture slot: " << sunTexture->GetAssignedSlot() << std::endl;
        std::cout << "Earth texture slot: " << earthTexture->GetAssignedSlot() << std::endl;
        std::cout << "Moon texture slot: " << moonTexture->GetAssignedSlot() << std::endl;
    }
}

void displaySoloar(GLFWwindow* window, double currentTime)
{
    //=========================��ʼ��========================================
    // �����ÿ֡���£���Ϊ������Ҫ��̬������
    Camera camera(
        glm::vec3(0, 0, 35),  // position
        glm::vec3(0, 0, 0),   // target
        glm::vec3(0, 1, 0),   // up
        45.0f, (float)g_WindowWidth / (float)g_WindowHeight, 0.1f, 100.0f
    );

    // ��Ⱦ��ÿ֡����������������
    Renderer renderer;
    renderer.SetDepthTest(true).SetPolygonMode(false).SetCullFace(false);
    renderer.Clear();

    //==========================���ñ任����========================================

    // ��ȡͶӰ����P
    Transform projectionTransform = camera.GetProjectionMatrix();
    transformStk.Push(projectionTransform);

    // ��ȡ��ͼ����V
    Transform viewTransform = camera.GetViewMatrix();
    transformStk.Push(viewTransform);

    // Transform����ÿ֡���������ڼ��㵱ǰ֡�ı任��
    Transform earthTransformPos, moonTransformPos, sunTransformPos;
    Transform earthTransformRotate, moonTransformRotate, sunTransformRotate;

    //----------------------------̫��------------------------------------------
    sunTransformPos.setPosition(0.0f, 0.0f, 0.0f);
    transformStk.Push(sunTransformPos);

    sunTransformRotate.setRotation((float)currentTime * 0.3f, 0, 0);  // ����̫����ת
    sunTransformRotate.setScale(1.2f, 1.2f, 1.2f);  // ��̫���Դ�һЩ
    transformStk.Push(sunTransformRotate);

    solarShader->SetUniformMat4fv("mvp_matrix", transformStk.Top().getMatrix());
    solarShader->SetUniform1i("objectType", 0); // sun
    renderer.Draw(*Sun, *solarShader, *sunTexture);
    transformStk.Pop();

    //----------------------------����------------------------------------------
    // ����ת��� - ������ԭ�е����õ���������
    float earthOrbitSpeed = (float)currentTime * 0.3f;  // ��������ת�ٶ�
    float earthX = sin(earthOrbitSpeed) * 18.0f;
    float earthZ = cos(earthOrbitSpeed) * 14.0f;
    
    earthTransformPos.setPosition(earthX, 0.0f, earthZ);
    transformStk.Push(earthTransformPos);

    earthTransformRotate.setRotation(0.0f, (float)currentTime * 2.0f, 0.0f);  // ���������ת
    earthTransformRotate.setScale(0.5f, 0.5f, 0.5f);
    transformStk.Push(earthTransformRotate);

    solarShader->SetUniformMat4fv("mvp_matrix", transformStk.Top().getMatrix());
    solarShader->SetUniform1i("objectType", 1); // earth
    renderer.Draw(*Earth, *solarShader, *earthTexture);
    transformStk.Pop();

    //----------------------------����------------------------------------------
    // �Ľ���������ϵͳ
    float moonOrbitSpeed = (float)currentTime * 1.5f;  // ����ת�ٶȣ��ȵ����һЩ��������
    float moonOrbitRadius = 2.0f;  // �������뾶������ڵ���
    
    // ��������ڵ����λ��
    float moonLocalX = sin(moonOrbitSpeed) * moonOrbitRadius;
    float moonLocalZ = cos(moonOrbitSpeed) * moonOrbitRadius;
    
    // �����΢�Ĺ����бЧ��
    float orbitTilt = sin(moonOrbitSpeed * 0.8f) * 0.3f;  // ��΢�����¸���
    
    // ��������λ�� = ����λ�� + ������Ե����λ��
    moonTransformPos.setPosition(
        moonLocalX, 
        orbitTilt,  // �����б�����Ĵ�ֱλ��
        moonLocalZ
    );
    transformStk.Push(moonTransformPos);

    // ������ת����΢�ȹ�ת��һ�㣬������ϫ�����Ľ���Ч����
    moonTransformRotate.setRotation(0.0f, moonOrbitSpeed * 0.9f, 0.0f);
    moonTransformRotate.setScale(0.2f, 0.2f, 0.2f);  // ���������С�ĳߴ�
    transformStk.Push(moonTransformRotate);

    solarShader->SetUniformMat4fv("mvp_matrix", transformStk.Top().getMatrix());
    solarShader->SetUniform1i("objectType", 2); // moon
    renderer.Draw(*Moon, *solarShader, *moonTexture);

    transformStk.Clear(); // ��ձ任ջ��׼����һ������ı任
}

// ������ - �ڳ������ʱ����
void SolarCleanup()
{
    delete sunTexture;
    delete earthTexture;
    delete moonTexture;
    delete solarShader;
    delete Sun;
    delete Earth;
    delete Moon;
    
    sunTexture = nullptr;
    earthTexture = nullptr;
    moonTexture = nullptr;
    solarShader = nullptr;
    Sun = nullptr;
    Earth = nullptr;
    Moon = nullptr;
}