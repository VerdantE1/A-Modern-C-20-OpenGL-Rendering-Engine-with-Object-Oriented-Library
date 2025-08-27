#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AllShaperTypes.h"
#include "Shader.h"
#include "Renderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Utility.h"
#include "Texture.h"  
#include "Ds/TransformStack.h"
#include "Globals.h"

class GLFWwindow;

// 全局变量声明
TransformStack transformStk;

// 全局纹理对象 - 在整个程序生命周期中保持
Texture* sunTexture = nullptr;
Texture* earthTexture = nullptr;
Texture* moonTexture = nullptr;
Texture* sunRingTexture = nullptr;  // 添加太阳环纹理

// 全局着色器和形状对象 - 避免每帧重新创建
Shader* solarShader = nullptr;
Sphere* Sun = nullptr;
ImportedModel* Earth = nullptr;
ImportedModel* Moon = nullptr;
Torus* SunRing = nullptr;  // 添加太阳环对象




void Solarinit()
{
    // 初始化形状对象
    Sun = new Sphere();
    Earth = new ImportedModel("res/objs/earth.obj");
    Moon = new ImportedModel("res/objs/earth.obj");

    
    // 创建太阳环 - 调整参数以获得合适的外观
    // majorRadius: 主半径(环的大小), minorRadius: 小半径(环的厚度)
    SunRing = new Torus(25.5f, 0.15f, 196, 16);  // 大环，较薄，高分辨率

    // 只初始化一次纹理对象
    if (sunTexture == nullptr) {
        sunTexture = new Texture("res/textures/2k_sun.jpg",
            TextureFilterMode::LINEAR,
            TextureFilterMode::LINEAR_MIPMAP_LINEAR,
            TextureWrapMode::REPEAT,
            TextureWrapMode::REPEAT,
            true,  // 生成mipmap
            true,
            AnisotropyLevel::HIGH); // 垂直翻转

        earthTexture = new Texture("res/textures/Earth.png",
            TextureFilterMode::LINEAR,
            TextureFilterMode::LINEAR_MIPMAP_LINEAR,
            TextureWrapMode::REPEAT,
            TextureWrapMode::REPEAT,
            true,  // 生成mipmap
            true,
            AnisotropyLevel::HIGH); // 垂直翻转

        moonTexture = new Texture("res/textures/2k_mercury.jpg",
            TextureFilterMode::LINEAR,
            TextureFilterMode::LINEAR_MIPMAP_LINEAR,
            TextureWrapMode::REPEAT,
            TextureWrapMode::REPEAT,
            true,  // 生成mipmap
            true,
            AnisotropyLevel::HIGH); // 垂直翻转

        // 为太阳环创建纹理 - 可以使用专门的环纹理或重用现有纹理
        sunRingTexture = new Texture("res/textures/2k_sun.jpg",  // 或使用专门的环纹理
            TextureFilterMode::LINEAR,
            TextureFilterMode::LINEAR_MIPMAP_LINEAR,
            TextureWrapMode::REPEAT,
            TextureWrapMode::REPEAT,
            true,  // 生成mipmap
            true,
            AnisotropyLevel::HIGH); // 垂直翻转

        // 初始化着色器（避免每帧重新加载）
        solarShader = new Shader("res/shaders/SoloarSystem.shader");

        // 打印初始化信息
        std::cout << "Solar System Initialized:" << std::endl;
        std::cout << "Sun texture slot: " << sunTexture->GetAssignedSlot() << std::endl;
        std::cout << "Earth texture slot: " << earthTexture->GetAssignedSlot() << std::endl;
        std::cout << "Moon texture slot: " << moonTexture->GetAssignedSlot() << std::endl;
        std::cout << "Sun Ring texture slot: " << sunRingTexture->GetAssignedSlot() << std::endl;
    }
}

void displaySoloar(GLFWwindow* window, double currentTime)
{
    //=========================初始化========================================
    // 摄像机每帧更新（因为可能需要动态调整）
    Camera camera(
        glm::vec3(0, 0, 45),  // position
        glm::vec3(0, 0, 0),   // target
        glm::vec3(0, 1, 0),   // up
        45.0f, (float)g_WindowWidth / (float)g_WindowHeight, 0.1f, 100.0f
    );

    // 渲染器每帧创建（轻量级对象）
    Renderer renderer;
    renderer.SetDepthTest(true).SetPolygonMode(false).SetCullFace(false).SetBlend(true);
    renderer.Clear();
    


    //==========================设置变换矩阵========================================

    // 获取投影矩阵P
    Transform projectionTransform = camera.GetProjectionMatrix();
    transformStk.Push(projectionTransform);

    // 获取视图矩阵V
    Transform viewTransform = camera.GetViewMatrix();
    transformStk.Push(viewTransform);

    // Transform对象每帧创建（用于计算当前帧的变换）
    Transform earthTransformPos, moonTransformPos, sunTransformPos;
    Transform earthTransformRotate, moonTransformRotate, sunTransformRotate;
    Transform sunRingTransform;  // 添加太阳环变换

    //----------------------------太阳------------------------------------------
    sunTransformPos.setPosition(0.0f, 0.0f, 0.0f);
    transformStk.Push(sunTransformPos);

    sunTransformRotate.setRotation((float)currentTime * 0.3f, 0, 0);  // 减慢太阳自转
    sunTransformRotate.setScale(6.9f, 6.9f, 6.9f);  // 让太阳稍大一些
    transformStk.Push(sunTransformRotate);

    solarShader->SetUniformMat4fv("mvp_matrix", transformStk.Top().getMatrix());
    solarShader->SetUniform1i("objectType", 0); // sun
    renderer.Draw(*Sun, *solarShader, *sunTexture);
    transformStk.Pop();

    //----------------------------太阳环------------------------------------------
    // 太阳环的旋转动画
    sunRingTransform.setRotation(
        sin((float)currentTime*0.05) * 0.5f,  
        cos((float)currentTime*0.05) * 0.5f,  
        sin((float)currentTime*0.05) * 0.5f
    );
    sunRingTransform.setScale(1.0f, 1.0f, 1.0f);  
    transformStk.Push(sunRingTransform);

    solarShader->SetUniformMat4fv("mvp_matrix", transformStk.Top().getMatrix());
    solarShader->SetUniform1i("objectType", 3); // sun ring - 新的类型
    renderer.Draw(*SunRing, *solarShader, *sunRingTexture);
    transformStk.Pop();
    transformStk.Pop();  // 弹出太阳的位置变换

    //----------------------------地球------------------------------------------
    // 地球公转轨道 - 保持您原有的设置但稍作调整
    float earthOrbitSpeed = (float)currentTime * 0.3f;  // 调整地球公转速度
    float earthX = sin(earthOrbitSpeed) * 18.0f;
    float earthZ = cos(earthOrbitSpeed) * 14.0f;
    
    earthTransformPos.setPosition(earthX, 0.0f, earthZ);
    transformStk.Push(earthTransformPos);

    earthTransformRotate.setRotation(0.0f, (float)currentTime * 0.5f, 0.0f);  // 地球快速自转
    earthTransformRotate.setScale(0.003f, 0.003f, 0.003f);
    transformStk.Push(earthTransformRotate);

    solarShader->SetUniformMat4fv("mvp_matrix", transformStk.Top().getMatrix());
    solarShader->SetUniform1i("objectType", 1); // earth
    renderer.DrawArrays(*Earth, *solarShader, *earthTexture, Earth->getNumVertices());
    transformStk.Pop();

    //----------------------------月球------------------------------------------
    // 改进的月球轨道系统
    float moonOrbitSpeed = (float)currentTime * 1.5f;  // 月球公转速度（比地球快一些，但合理）
    float moonOrbitRadius = 2.0f;  // 月球轨道半径（相对于地球）
    
    // 月球相对于地球的位置
    float moonLocalX = sin(moonOrbitSpeed) * moonOrbitRadius;
    float moonLocalZ = cos(moonOrbitSpeed) * moonOrbitRadius;
    
    // 添加轻微的轨道倾斜效果
    float orbitTilt = sin(moonOrbitSpeed * 0.8f) * 0.3f;  // 轻微的上下浮动
    
    // 月球最终位置 = 地球位置 + 月球相对地球的位置
    moonTransformPos.setPosition(
        moonLocalX, 
        orbitTilt,  // 轨道倾斜产生的垂直位移
        moonLocalZ
    );
    transformStk.Push(moonTransformPos);

    // 月球自转（稍微比公转慢一点，产生潮汐锁定的近似效果）
    moonTransformRotate.setRotation(0.0f, moonOrbitSpeed * 0.9f, 0.0f);
    moonTransformRotate.setScale(0.001f, 0.001f, 0.001f);  // 保持月球较小的尺寸
    transformStk.Push(moonTransformRotate);

    solarShader->SetUniformMat4fv("mvp_matrix", transformStk.Top().getMatrix());
    solarShader->SetUniform1i("objectType", 2); // moon
    renderer.DrawArrays(*Moon, *solarShader, *moonTexture, Moon->getNumVertices());
    transformStk.Pop();
    
    transformStk.Clear(); // 清空变换栈，准备下一个物体的变换


}

// 清理函数 - 在程序结束时调用
void SolarCleanup()
{
    delete sunTexture;
    delete earthTexture;
    delete moonTexture;
    delete sunRingTexture;  // 清理太阳环纹理
    delete solarShader;
    delete Sun;
    delete Earth;
    delete Moon;
    delete SunRing;  // 清理太阳环对象
    
    sunTexture = nullptr;
    earthTexture = nullptr;
    moonTexture = nullptr;
    sunRingTexture = nullptr;
    solarShader = nullptr;
    Sun = nullptr;
    Earth = nullptr;
    Moon = nullptr;
    SunRing = nullptr;
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
