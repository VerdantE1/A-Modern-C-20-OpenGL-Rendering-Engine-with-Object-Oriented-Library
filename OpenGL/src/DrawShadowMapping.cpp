#include "Globals.h"
#include <memory>
#include <utility>

#include "Logger.h"

#include "Entity.h"
#include "Scene.h" 
#include "LightComponent.h"
#include "RenderComponent.h"    
#include "RotationAnimation.h"  
#include "ShadowComponent.h"
#include "Camera.h"             
#include "GlobalLight.h"        
#include "Renderer.h"           
#include "BaseScene.h"
#include "SceneManager.h"
#include "Engine.h"

void enityInitializer_func(Scene* scene) {
    // 创建Torus实体
    auto E_rightToruhs = scene->CreateEntity("rightTorus");
    {
        auto renderComp = E_rightToruhs->AddComponent<RenderComponent>(
            global_torusPtr,
            shadowMappingRenderShaderPtr
        );
        E_rightToruhs->AddComponent<RotationAnimation>(1.75f);
        E_rightToruhs->AddComponent<MaterialComponent>(MaterialComponent::MaterialType::GOLD);
        E_rightToruhs->GetTransform()->SetPosition(3.0f, 0.0f, -2.0f);
		E_rightToruhs->GetTransform()->SetScale(1.0f,1.0f,1.0f);
    }

    // 创建Sphere实体
    auto E_leftSphere = scene->CreateEntity("leftSphere");
    {
        auto renderComp2 = E_leftSphere->AddComponent<RenderComponent>(
            global_spherePtr,
            shadowMappingRenderShaderPtr
        );
        E_leftSphere->AddComponent<RotationAnimation>(1.75f);
        E_leftSphere->AddComponent<MaterialComponent>(MaterialComponent::MaterialType::SILVER);
        E_leftSphere->GetTransform()->SetPosition(-3.0f, 0.0f, -2.0f);
        E_leftSphere->GetTransform()->SetScale(1.0f, 1.0f, 1.0f);
    }

    auto E_ground = scene->CreateEntity("ground");
    {
        auto renderComp = E_ground->AddComponent<RenderComponent>(
            global_cubePtr,  // 使用立方体作为地面
            shadowMappingRenderShaderPtr
        );
        E_ground->AddComponent<MaterialComponent>(MaterialComponent::MaterialType::SILVER);

        // 创建一个扁平的地面
        E_ground->GetTransform()->SetPosition(0.0f, -3.0f, -6.0f);  // 在物体下方
        E_ground->GetTransform()->SetScale(12.0f, 0.1f, 12.0f);     // 大而扁平的地面
    }


    // 创建光源实体
    auto E_light = scene->CreateEntity("light");
    {
        // 添加光源组件
        auto lightComp = E_light->AddComponent<LightComponent>();
        lightComp->SetLightType(LightComponent::LightType::POINT);
        lightComp->SetAmbient(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
        lightComp->SetDiffuse(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));  // 白光
        lightComp->SetSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        lightComp->SetIntensity(1.0f);

        E_light->GetTransform()->SetPosition({ 5.0f, 2.0f, 2.0f });

        // 添加阴影组件
        E_light->AddComponent<ShadowComponent>();
    }
}





void DrawShadowMappingWithECS(GLFWwindow* window) {

    InitializeGlobalShaders();
    InitializeGlobalObjects(); 

    //创建引擎
    Engine engine;

    //创建并设置场景
    auto scene = std::make_unique<BaseScene>();

    scene->SetEntityInitializer(enityInitializer_func);

    // 设置键盘处理
    engine.SetKeyboardHandler([&](int key, int action) {
        switch (key) {
        case GLFW_KEY_G:
            glfwSetWindowTitle(window, "全部使用 Gouraud 着色（ECS版本）");
            // TODO: 实现切换着色器逻辑
            break;
        case GLFW_KEY_P:
            glfwSetWindowTitle(window, "全部使用 Phong 着色（ECS版本）");
            // TODO: 实现切换着色器逻辑
            break;
        case GLFW_KEY_C:
            glfwSetWindowTitle(window, "对比模式（ECS版本）");
            // TODO: 恢复原始着色器
            break;
        }
        });

	engine.SetScene(std::move(scene));
    engine.Run(window);
}
