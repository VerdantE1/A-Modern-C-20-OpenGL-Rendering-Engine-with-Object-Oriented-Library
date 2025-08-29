#include "Globals.h"
#include <memory>
#include <utility>

#include "Logger.h"

#include "Entity.h"
#include "Scene.h" 
#include "LightComponent.h"
#include "RenderComponent.h"    
#include "RotationAnimation.h"  
#include "Camera.h"             
#include "GlobalLight.h"        
#include "Renderer.h"           




class BaseScene : public Scene {
public:
    using EnityInitializer = std::function<void(Scene*)>;

    void Initialize() override {
		LOG_INFO("BaseScene: Initializing scene...");

        // 1. Configure renderer first
        m_renderer.SetPolygonMode(false).SetDepthTest(true);  // ← ADD THIS LINE

        // 2. 创建摄像机
        SetCamera(std::make_unique<Camera>(cameraConfig.CreateCamera()));

        // 3. 设置全局光源
        SetGlobalLight();

        // 4. 初始化实体
        InlitializeEntities(enityInitializer);

        // 5. 建立光源索引
        BuildLightIndex();

        LOG_INFO("\tEntities initialized: Count={}", m_Entities.size());
        LOG_INFO("\tLights indexed: Count={}", m_lightIndex.size());

    }

    // 只会更新C++中的逻辑，不会更新GLSL中的任何东西,uniform的更新需要在Render中进行
    void Update(float delataTime) override {
        //1.通用更新
        UpdateAllEntity(delataTime);        // 只调用 Component::Update


        //2.光照更新
        UpdateDynamicLights(delataTime);    // 更新动态光源位置等


    }

    void Render(const Renderer& renderer) override {
        LOG_TRACE("BaseScene: Starting render");

        renderer.Clear();     // 使用传入的 renderer
        glm::mat4 view = GetCamera().GetViewMatrix();
        glm::mat4 projection = GetCamera().GetProjectionMatrix();

        // 使用传入的 renderer
        RenderAllEntities(renderer, view, projection);

        LOG_TRACE("BaseScene: Render complete");
    }

    // 设置实体初始化器
    void SetEntityInitializer(EnityInitializer initializer) {
        enityInitializer = initializer;
    }

    void Cleanup() override {
        m_Entities.clear();
        m_NamedEntities.clear();
	}

    Renderer& GetRenderer() { return m_renderer; }

private:
    CameraConfig cameraConfig;
    EnityInitializer enityInitializer;
    GlobalLight m_globalLight;
    Renderer m_renderer;
	std::unordered_map<std::string, LightComponent*> m_lightIndex; // 局部光源索引


    void RenderAllEntities(const Renderer& renderer, const glm::mat4& view, const glm::mat4& projection)
    {
        LOG_DEBUG("\tRendering {} entities", m_Entities.size());

        for (auto& entity : m_Entities) {
            auto renderComp = entity->GetComponent<RenderComponent>();
            auto transform = entity->GetTransform();

            // 跳过没有RenderComponent的Entity（如光源Entity）
            if (!renderComp || !transform) {
                continue;
            }

            auto shader = renderComp->GetShader();
            auto geometry = renderComp->GetGeometry();

            if (!shader || !geometry || shader->GetID() == 0) {
                LOG_ERROR("\t\tEntity '{}' has invalid render components", entity->GetName());
                continue;
            }

            shader->Bind();
            LOG_DEBUG("\t\tRendering entity '{}' with shader ID {}", entity->GetName(), shader->GetID());

          
            // 应用全局光照
            ApplyGlobalLightToShader(*renderComp);

            // 快速应用局部光源数据（无需遍历）
            ApplyIndexedLightsToShader(*shader, view);

            // 执行渲染
            renderComp->Render(renderer, projection, view, transform->GetMatrix());
            LOG_DEBUG("\t\tEntity '{}' rendered successfully", entity->GetName());
        }
        LOG_DEBUG("\tAll entities rendered");
    }

    void BuildLightIndex() {
        m_lightIndex.clear();
        for (auto& entity : m_Entities) {
            auto lightComp = entity->GetComponent<LightComponent>();
            if (lightComp) {
                m_lightIndex[entity->GetName()] = lightComp;
                LOG_DEBUG("Indexed light: {}", entity->GetName());
            }
        }
    }

    //  使用索引快速应用光源
    void ApplyIndexedLightsToShader(Shader& shader, const glm::mat4& view) {
        if (m_lightIndex.empty()) {
            LOG_WARNING("No indexed lights found");
            return;
        }

        // 取第一个光源（可扩展为多光源支持）
        auto lightIt = m_lightIndex.begin();
        auto* lightComp = lightIt->second;

        if (lightComp && lightComp->enabled) {
            auto* lightEntity = lightComp->GetOwner();

            // 获取光源位置并转换到视图空间
            if (auto transform = lightEntity->GetTransform()) {
                glm::vec3 worldPos = transform->GetPosition();
                glm::vec3 viewPos = glm::vec3(view * glm::vec4(worldPos, 1.0f));

				//TODO: 目前只支持多个LightComponent,但它们会重复覆盖同一个"light.position" uniform
				//后续要改成数组形式的 uniform 来支持多个光源
                shader.SetUniform3f("light.position", viewPos.x, viewPos.y, viewPos.z);
                LOG_DEBUG("\t\t\tLight '{}' position (view): ({}, {}, {})",
                    lightEntity->GetName(), viewPos.x, viewPos.y, viewPos.z);
            }

            // 应用光源属性
            shader.SetUniform4f("light.ambient",
                lightComp->ambient.r * lightComp->intensity,
                lightComp->ambient.g * lightComp->intensity,
                lightComp->ambient.b * lightComp->intensity,
                lightComp->ambient.a);
            shader.SetUniform4f("light.diffuse",
                lightComp->diffuse.r * lightComp->intensity,
                lightComp->diffuse.g * lightComp->intensity,
                lightComp->diffuse.b * lightComp->intensity,
                lightComp->diffuse.a);
            shader.SetUniform4f("light.specular",
                lightComp->specular.r * lightComp->intensity,
                lightComp->specular.g * lightComp->intensity,
                lightComp->specular.b * lightComp->intensity,
                lightComp->specular.a);
        }
    }

    void AddLightToIndex(const std::string& name, LightComponent* lightComp) {
        m_lightIndex[name] = lightComp;
    }

    void RemoveLightFromIndex(const std::string& name) {
        m_lightIndex.erase(name);
    }


    void SetGlobalLight() {
        // 设置全局环境光
        m_globalLight.SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f)); // 设置合适的环境光
        // m_globalLight.SetDiffuse(glm::vec3(0.1f, 0.1f, 0.1f));
        // m_globalLight.SetSpecular(glm::vec3(0.0f, 0.0f, 0.0f));
    }

    void ApplyGlobalLightToAllShaders() {
        for (auto& entity : m_Entities) {
            auto renderComp = entity->GetComponent<RenderComponent>();
            if (renderComp) {
                auto shader = renderComp->GetShader();
                if (shader) {
                    m_globalLight.ApplyToShader(*shader);
                }
            }
        }
    }


    void InlitializeEntities(EnityInitializer initializer) {
        enityInitializer = initializer;
        enityInitializer(this);
    }


    void UpdateAllEntity(float deltaTime) {
        for (auto& entity : m_Entities) {
            entity->UpdateAllComponent(deltaTime);
        }
    }

    // 可选：更新动态光源位置等
    void UpdateDynamicLights(float deltaTime) {
        float currentTime = static_cast<float>(glfwGetTime());
        currentLightPos = glm::vec3(
            initialLightLoc.x + sin(currentTime * 0.8f) * 3.0f,
            initialLightLoc.y + cos(currentTime * 0.6f) * 2.0f,
            initialLightLoc.z
        );
        // 更新所有光源组件的位置
        for (auto& entity : m_Entities) {
            auto lightComp = entity->GetComponent<LightComponent>();
            if (lightComp) {
                entity->GetTransform()->SetPosition(currentLightPos);
            }
        }
    }

    void ApplyGlobalLightToShader(RenderComponent& renderComp) {
        auto shader = renderComp.GetShader();
        if(!shader) {
            LOG_ERROR("RenderComponent has no shader to apply global light.");
            return;
		}
        m_globalLight.ApplyToShader(*shader);
        
    }
};

void enityInitializer_func(Scene* scene) {
    // 创建Torus实体
    auto E_rightToruhs = scene->CreateEntity("rightTorus");
    auto renderComp = E_rightToruhs->AddComponent<RenderComponent>(
        global_torusPtr,
        gouraudShaderPtr
    );
    E_rightToruhs->AddComponent<RotationAnimation>(1.75f);
    E_rightToruhs->AddComponent<MaterialComponent>(MaterialComponent::MaterialType::GOLD);
    E_rightToruhs->GetTransform()->SetPosition(3.0f, 0.0f, -5.0f);

    // 创建Sphere实体
    auto E_leftSphere = scene->CreateEntity("leftSphere");
    auto renderComp2 = E_leftSphere->AddComponent<RenderComponent>(
        global_spherePtr,
        blinnPhongShaderPtr
    );
    E_leftSphere->AddComponent<RotationAnimation>(1.75f);
    E_leftSphere->AddComponent<MaterialComponent>(MaterialComponent::MaterialType::SILVER);
    E_leftSphere->GetTransform()->SetPosition(-3.0f, 0.0f, -5.0f);


    // 创建光源实体
    auto E_light = scene->CreateEntity("light");
    auto lightComp = E_light->AddComponent<LightComponent>();
    lightComp->SetLightType(LightComponent::LightType::POINT);
    lightComp->SetAmbient(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    lightComp->SetDiffuse(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));  // 白光
    lightComp->SetSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    lightComp->SetIntensity(1.0f);
    
    E_light->GetTransform()->SetPosition({ 5.0f, 2.0f, 2.0f });
}

class SceneManager {
public:
	SceneManager() = default;
	~SceneManager() = default;

    //设置当前活动场景
    void SetActiveScene(std::unique_ptr<Scene> scene) {
        if (m_currentScene) {
            m_currentScene->Cleanup();
        }
		m_currentScene = std::move(scene);
        if (m_currentScene) {
			m_currentScene->Initialize();
        }
    }

	//获取当前活动场景
	Scene* GetActiveScene() const { return m_currentScene.get(); }

	//更新当前场景
    void Update(float deltaTime){
        if (m_currentScene) {
            m_currentScene->Update(deltaTime);
        }
	}

    //渲染当前场景
    void Render() {
        if (m_currentScene) {
            m_currentScene->Render(m_currentScene->GetRenderer());
        }
    }

	//清理当前场景
    void Cleanup() {
        if (m_currentScene) {
            m_currentScene->Cleanup();
            m_currentScene.reset();
        }
	}
private:
	std::unique_ptr<Scene> m_currentScene = nullptr;
};


class Engine {
public:
    using KeyboardHandler = std::function<void(int key, int action)>;

	WindowConfig windowConfig;
	SceneManager sceneManager;

    void Run(GLFWwindow* window) {


		auto scene = sceneManager.GetActiveScene();
        if (!scene)
        {
			LOG_ERROR("No active scene set in SceneManager. Exiting Run loop.");
			return;
        }

		//主循环
        while (!glfwWindowShouldClose(window)) {
			LOG_SUCCESS("New frame start.");

            
            LOG_LEVEL_INFO(1,"Engine: Processing UpdateTime and Input ");
            UpdateTime();
            HandleInput(window);
			LOG_INFO("\tEngine: Compelete UpdateTime and Input. DeltaTime = {}", deltaTime);

            
			//通过SceneManager渲染当前场景
            LOG_LEVEL_INFO(1, "Engine: Updating Data in CPU");
			sceneManager.Update(deltaTime); 
            LOG_LEVEL_INFO(1, "Engine: Finished Data in CPU");


			LOG_LEVEL_INFO(1, "Engine: Rendering Scene in GPU");
            sceneManager.Render();
			LOG_LEVEL_INFO(1, "Engine: Finished Rendering Scene in GPU");
            
			glfwSwapBuffers(window);
			glfwPollEvents();

            LOG_SUCCESS("Frame end.");

        }
		// 清理场景
		sceneManager.Cleanup();
    }
    void SetKeyboardHandler(KeyboardHandler handler) { globalInputHandler = handler; }
	void SetScene(std::unique_ptr<Scene> scene) { sceneManager.SetActiveScene(std::move(scene)); }

protected:
	KeyboardHandler globalInputHandler = nullptr;

    float lastTime = 0.0f;
	float deltaTime = 0.0f;
	float currentTime = 0.0f;
    
    void UpdateTime() {
        currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
    }

    void HandleInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        if (!globalInputHandler) return;
        // 简单的键盘处理
        static double lastKeyTime = 0.0;
        if (currentTime - lastKeyTime > 0.3) { // 防抖
            if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
                globalInputHandler(GLFW_KEY_G, GLFW_PRESS);
                lastKeyTime = currentTime;
            }
            else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
                globalInputHandler(GLFW_KEY_P, GLFW_PRESS);
                lastKeyTime = currentTime;
            }
            else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
                globalInputHandler(GLFW_KEY_C, GLFW_PRESS);
                lastKeyTime = currentTime;
            }
        }
    }
};




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
