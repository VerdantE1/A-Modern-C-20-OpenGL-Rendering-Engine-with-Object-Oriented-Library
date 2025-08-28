#include "Globals.h"
#include <memory>
#include <utility>
#include "IO/KeyBoard.h"

#include "DrawDemoUtils.h"

#include "Entity.h"
#include "Scene.h"
#include "LightComponent.h"



class SceneManager {

};


class Engine {
public:
    using KeyboardHandler = std::function<void(int key, int action)>;


	WindowConfig windowConfig;
	SceneManager sceneManager;

    void Run();
    void SetKeyboardHandler(KeyboardHandler handler) { globalInputHandler = handler; }
 
protected:
	KeyboardHandler globalInputHandler = nullptr;
    
};


class BaseScene : public Scene {
public:
    using EnityInitializer = std::function<void(Scene*)>;
	

    void Initialize() override {
        // 1. 创建摄像机
        SetCamera(std::make_unique<Camera>(cameraConfig.CreateCamera())); 

        // 2. 设置全局光源
		SetGlobalLight(); 

        // 3. 初始化实体
		InlitializeEntities(enityInitializer); 

        // 4. 全局光应用到所有着色器
		ApplyGlobalLightToAllShaders(); 

       
    }

	// 只会更新C++中的逻辑，不会更新GLSL中的任何东西,uniform的更新需要在Render中进行
    void Update(float delataTime) override {
		//1.通用更新
		UpdateTime();                       // 更新时钟
		UpdateAllEntity(delataTime);        // 只调用 Component::Update

		//2.光照更新
		UpdateDynamicLights(delataTime);    // 更新动态光源位置等
		
    }

    void Render(const Renderer& renderer) override {
        m_renderer.Clear();     // 清屏
        glm::mat4 view = GetCamera().GetViewMatrix();
        glm::mat4 projection = GetCamera().GetProjectionMatrix();
    }
    

private:
    CameraConfig cameraConfig;
    EnityInitializer enityInitializer;
	GlobalLight m_globalLight;
	Renderer m_renderer;

	float lastFrameTime = 0.0f;
	float deltaTime = 0.0f;
	float currentTime = 0.0f;

    void RenderAllEntities(const Renderer& renderer, const glm::mat4& view, const glm::mat4& projection)
    {
        for (auto& entity : m_Entities) {
            auto renderComp = entity->GetComponent<RenderComponent>();
            auto transform = entity->GetTransform();

            if (renderComp && transform) {
				//应用全局光照
                ApplyGlobalLightToShader(*renderComp);
				
				//执行渲染（会自动调用所有组件的 ApplyToShader）
				renderComp->Render(renderer, projection, view, transform->GetMatrix()); //执行渲染（会自动应用 ShaderDataComponent 的数据）

            }

        }
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

    void UpdateTime() {
        currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;
	}

	void ApplyGlobalLightToShader(RenderComponent& renderComp) {
        auto shader = renderComp.GetShader();
        if (shader) {
            m_globalLight.ApplyToShader(*shader);
        }
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
    E_rightToruhs->GetTransform()->SetPosition(3.0f, 0.0f, -5.0f);

	// 创建Sphere实体
    auto E_leftSphere = scene->CreateEntity("leftSphere");
    auto renderComp2 = E_leftSphere->AddComponent<RenderComponent>(
        global_spherePtr,
        gouraudShaderPtr
	);
    E_leftSphere->AddComponent<RotationAnimation>(1.75f);
    E_leftSphere->GetTransform()->SetPosition(-3.0f, 0.0f, -5.0f);


	// 创建光源实体
    auto E_light = scene->CreateEntity("light");
    auto lightComp = E_light->AddComponent<LightComponent>();
    lightComp->SetLightType(LightComponent::LightType::POINT);
    E_light->GetTransform()->SetPosition({ 5.0f, 2.0f, 2.0f });


}

void DrawShadowMapping(GLFWwindow* window)
{
    // 创建两个着色器
    Shader gouraudShader("res/shaders/Gouraud.shader");
    Shader phongShader("res/shaders/Blinn-Phong.Shader");

    // 创建两个 Torus 对象
    Sphere leftsphere;   // 左侧用 Gouraud
    Torus rightTorus;  // 右侧用 Phong

    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;

    // 摄像机初始化
    Camera camera(
        glm::vec3(0, 0, 8), // 后退更远以便看到两个 torus
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0),
        70.0f, aspect, 0.1f, 100.0f
    );

    // 左侧 Torus (Gouraud)
    Transform leftsphereTransform;
    leftsphereTransform.setPosition(-3.0f, 0.0f, -5.0f);

    // 右侧 Torus (Phong)  
    Transform rightTorusTransform;
    rightTorusTransform.setPosition(3.0f, 0.0f, -5.0f);

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.GetProjectionMatrix();

    Renderer renderer;
    renderer.SetPolygonMode(false).SetDepthTest(true);

    // 跟踪当前使用的着色器
    bool useGouraudForBoth = false;
    bool usePhongForBoth = false;
    double lastKeyPressTime = 0.0;

    // 设置初始窗口标题
    glfwSetWindowTitle(window, "Gouraud vs Phong | [G]All Gouraud | [P]All Phong | [C]Compare Pattern | [SPACE]Toggle Light");

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        float currentTime = static_cast<float>(glfwGetTime());

        // 键盘输入处理
        if ((currentTime - lastKeyPressTime) > 0.3) {
            if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
                useGouraudForBoth = true;
                usePhongForBoth = false;
                glfwSetWindowTitle(window, "全部使用 Gouraud 着色 | [C]返回对比模式");
                lastKeyPressTime = currentTime;
            }
            else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
                useGouraudForBoth = false;
                usePhongForBoth = true;
                glfwSetWindowTitle(window, "全部使用 Phong 着色 | [C]返回对比模式");
                lastKeyPressTime = currentTime;
            }
            else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
                useGouraudForBoth = false;
                usePhongForBoth = false;
                glfwSetWindowTitle(window, "对比模式: 左侧Gouraud | 右侧Phong");
                lastKeyPressTime = currentTime;
            }
        }

        // 动画计算
        float animX = sin(0.35f * currentTime) * 0.5f;  // 减小旋转幅度

        // 更新两个 Torus 的变换
        leftsphereTransform.setRotation(animX, currentTime * 0.5f, 0.0f);
        rightTorusTransform.setRotation(animX, currentTime * 0.5f, 0.0f);

        // 设置光源
        currentLightPos = glm::vec3(
            initialLightLoc.x + sin(currentTime * 0.8f) * 3.0f,  // 光源左右移动
            initialLightLoc.y + cos(currentTime * 0.6f) * 2.0f,  // 光源上下移动
            initialLightLoc.z
        );

        // ===== 绘制左侧 Torus =====
        glm::mat4 leftMv = view * leftsphereTransform.getMatrix();
        glm::mat4 leftNormal = glm::transpose(glm::inverse(leftMv));

        // 选择左侧使用的着色器
        Shader* leftShader = &gouraudShader;
        if (usePhongForBoth) leftShader = &phongShader;

        installLights(view, *leftShader);
        leftShader->SetUniformMat4fv("mv_matrix", leftMv);
        leftShader->SetUniformMat4fv("proj_matrix", projection);
        leftShader->SetUniformMat4fv("norm_matrix", leftNormal);
        renderer.Draw(leftsphere, *leftShader);

        // ===== 绘制右侧 Torus =====
        glm::mat4 rightMv = view * rightTorusTransform.getMatrix();
        glm::mat4 rightNormal = glm::transpose(glm::inverse(rightMv));

        // 选择右侧使用的着色器
        Shader* rightShader = &phongShader;
        if (useGouraudForBoth) rightShader = &gouraudShader;

        installLights(view, *rightShader);
        rightShader->SetUniformMat4fv("mv_matrix", rightMv);
        rightShader->SetUniformMat4fv("proj_matrix", projection);
        rightShader->SetUniformMat4fv("norm_matrix", rightNormal);
        renderer.Draw(rightTorus, *rightShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}
