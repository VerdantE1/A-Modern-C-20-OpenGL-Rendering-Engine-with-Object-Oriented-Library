#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>
#include <memory>

#include "Utility.h"
#include "Texture.h"
#include "Renderer.h"
#include "Camera.h"
#include "AllShaperTypes.h"
#include "Globals.h"
#include "Transform.h"

// 引入 ECS 系统
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Scene/Component.h"
#include "Scene/Components/TransformComponent.h"
#include "Scene/Components/RenderComponent.h"
#include "Scene/Components/RotationAnimation.h"
#include "Scene/Components/OrbitAnimation.h"
#include "Scene/Components/LightComponent.h"




// ==================== 键盘输入处理器 ====================================
struct KeyboardHandler {
	std::function<void(int key, int action)> onKeyPress;
	double lastKeyTime = 0.0;
	double keyDelay = 0.3; // 防止连续触发

	void Update(GLFWwindow* window) {
		double currentTime = glfwGetTime();
		if (currentTime - lastKeyTime < keyDelay) return;

		//常用按键检测
		for (int key = GLFW_KEY_A; key <= GLFW_KEY_Z; ++key) {
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				if (onKeyPress) onKeyPress(key, GLFW_PRESS);
				lastKeyTime = currentTime;
				break;
			}
		}
		// 特殊按键
		int specialKeys[] = { GLFW_KEY_SPACE, GLFW_KEY_ENTER, GLFW_KEY_ESCAPE,
						   GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_LEFT, GLFW_KEY_RIGHT };
		for (int key : specialKeys) {
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				if (onKeyPress) onKeyPress(key, GLFW_PRESS);
				lastKeyTime = currentTime;
				break;
			}
		}
	}
};

// ==================== 主渲染循环模板 ====================
template<typename SetupFunc, typename UpdateFunc, typename RenderFunc>
void RunRenderLoop(GLFWwindow* window,
	SetupFunc setup,
	UpdateFunc update,
	RenderFunc render) {
	// 执行设置
	setup();

	float lastTime = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		float currentTime = static_cast<float>(glfwGetTime());
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// 更新
		update(currentTime, deltaTime);

		// 渲染
		render(currentTime, deltaTime);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

// ============================ ECS 驱动的简单场景基类 =============================
class SimpleScene : public Scene {
public:
	WindowConfig windowConfig;
	CameraConfig cameraConfig;
	RenderConfig renderConfig;
	KeyboardHandler keyboard;
	GLFWwindow* m_Window = nullptr;

	void InitializeWithWindow(GLFWwindow* window) {
		m_Window = window;
		windowConfig.UpdateFromWindow(window);
		SetCamera(std::make_unique<Camera>(cameraConfig.CreateCamera(windowConfig.aspectRatio)));
	}

	void Initialize() override {

	}

	void Update(float deltaTime) override {
		if (m_Window) {
			keyboard.Update(m_Window);
		}
		// 更新所有实体的组件
		UpdateAllEntities(deltaTime);
	}

	void Render(const Renderer& renderer) override {
		// 应用渲染配置
		renderConfig.ApplyToRenderer(const_cast<Renderer&>(renderer));
		renderer.Clear();

		// 获取摄像机矩阵
		glm::mat4 view = GetCamera().GetViewMatrix();
		glm::mat4 projection = GetCamera().GetProjectionMatrix();

		// 渲染所有带有 RenderComponent 的实体
		RenderAllEntities(renderer, view, projection);
	}

	void Cleanup() override {
		m_Entities.clear();
	}

	// 便利方法：创建带有基本组件的实体
	template<typename GeometryType>
	Entity* CreateRenderableEntity(const std::string& name,
		const std::string& shaderPath,
		const std::string& texturePath = "") {
		auto entity = CreateEntity(name);

		auto renderComp = entity->AddComponent<RenderComponent>();
		renderComp->SetGeometry(std::make_shared<GeometryType>());
		renderComp->SetShader(std::make_shared<Shader>(shaderPath));

		if (!texturePath.empty()) {
			renderComp->SetTexture(std::make_shared<Texture>(texturePath));
		}

		return entity;
	}

	// 便利方法：创建带有旋转动画的实体
	template<typename GeometryType>
	Entity* CreateRotatingEntity(const std::string& name,
		const std::string& shaderPath,
		float rotationSpeed = 1.0f,
		const glm::vec3& axis = glm::vec3(0, 1, 0)) {
		auto entity = CreateRenderableEntity<GeometryType>(name, shaderPath);
		entity->AddComponent<RotationAnimation>(rotationSpeed, axis);
		return entity;
	}

	// 便利方法：创建带有圆周运动的实体
	template<typename GeometryType>
	Entity* CreateOrbitingEntity(const std::string& name,
		const std::string& shaderPath,
		float radius = 3.0f,
		float orbitSpeed = 1.0f,
		const glm::vec3& center = glm::vec3(0)) {
		auto entity = CreateRenderableEntity<GeometryType>(name, shaderPath);
		entity->AddComponent<OrbitAnimation>(radius, orbitSpeed, center);
		return entity;
	}


private:
	void UpdateAllEntities(float deltaTime) {
		for (auto& entity : m_Entities) {
			// 更新旋转动画
			auto rotationAnim = entity->GetComponent<RotationAnimation>();
			if (rotationAnim) {
				rotationAnim->Update(deltaTime);
			}

			// 更新圆周运动
			auto orbitAnim = entity->GetComponent<OrbitAnimation>();
			if (orbitAnim) {
				orbitAnim->Update(deltaTime);
			}

			// 可以在这里添加更多组件的更新逻辑
		}
	}

	void RenderAllEntities(const Renderer& renderer,
		const glm::mat4& view,
		const glm::mat4& projection) {
		for (auto& entity : m_Entities) {
			auto renderComp = entity->GetComponent<RenderComponent>();
			auto transform = entity->GetTransform();

			if (renderComp && transform) {
				renderComp->Render(renderer, projection, view, transform->GetMatrix());
			}
		}
	}

};
// ============================ 专门的场景类型 =============================

// 单个旋转物体场景
template<typename GeometryType>
class SingleRotatingObjectScene : public SimpleScene {
public:
	SingleRotatingObjectScene(const std::string& shaderPath, 
							 const std::string& texturePath = "",
							 float rotationSpeed = 1.75f) 
		: m_ShaderPath(shaderPath), m_TexturePath(texturePath), m_RotationSpeed(rotationSpeed) {}

	void Initialize() override {
		auto entity = CreateRotatingEntity<GeometryType>("MainObject", m_ShaderPath, m_RotationSpeed);
		
		if (!m_TexturePath.empty()) {
			auto renderComp = entity->GetComponent<RenderComponent>();
			renderComp->SetTexture(std::make_shared<Texture>(m_TexturePath));
		}

		// 设置初始位置
		entity->GetTransform()->SetPosition(0, 0, -5);
	}

private:
	std::string m_ShaderPath;
	std::string m_TexturePath;
	float m_RotationSpeed;
};

// 双对象对比场景（用于着色器对比等）
template<typename LeftGeometry, typename RightGeometry>
class DualObjectScene : public SimpleScene {
public:
	DualObjectScene(const std::string& leftShader, 
				   const std::string& rightShader,
				   bool needsLighting = false)
		: m_LeftShader(leftShader), m_RightShader(rightShader), m_NeedsLighting(needsLighting) {}

	void Initialize() override {
		// 创建左侧对象
		m_LeftEntity = CreateRotatingEntity<LeftGeometry>("LeftObject", m_LeftShader);
		m_LeftEntity->GetTransform()->SetPosition(-3.0f, 0, -5);
		
		// 创建右侧对象
		m_RightEntity = CreateRotatingEntity<RightGeometry>("RightObject", m_RightShader);
		m_RightEntity->GetTransform()->SetPosition(3.0f, 0, -5);

		if (m_NeedsLighting) {
			// 设置光照
			auto leftRender = m_LeftEntity->GetComponent<RenderComponent>();
			auto rightRender = m_RightEntity->GetComponent<RenderComponent>();
			
			if (leftRender) leftRender->SetNeedsNormalMatrix(true);
			if (rightRender) rightRender->SetNeedsNormalMatrix(true);
		}

		// 设置键盘回调
		SetupKeyboardHandlers();
	}

	void Update(float deltaTime) override {
		SimpleScene::Update(deltaTime);

		// 更新动态光源（如果启用光照）
		if (m_NeedsLighting) {
			UpdateDynamicLight(deltaTime);
		}
	}

protected:
	Entity* m_LeftEntity = nullptr;
	Entity* m_RightEntity = nullptr;
	bool m_UseLeftShaderForBoth = false;
	bool m_UseRightShaderForBoth = false;

	virtual void SetupKeyboardHandlers() {
		keyboard.onKeyPress = [this](int key, int action) {
			switch (key) {
				case GLFW_KEY_G: // 全部使用左侧着色器
					SwitchToLeftShader();
					break;
				case GLFW_KEY_P: // 全部使用右侧着色器
					SwitchToRightShader();
					break;
				case GLFW_KEY_C: // 恢复对比模式
					RestoreOriginalShaders();
					break;
			}
		};
	}

	void SwitchToLeftShader() {
		if (m_LeftEntity && m_RightEntity) {
			auto leftRender = m_LeftEntity->GetComponent<RenderComponent>();
			auto rightRender = m_RightEntity->GetComponent<RenderComponent>();
			
			if (leftRender && rightRender) {
				rightRender->SetShader(leftRender->GetShader());
			}
		}
		m_UseLeftShaderForBoth = true;
		m_UseRightShaderForBoth = false;
	}

	void SwitchToRightShader() {
		if (m_LeftEntity && m_RightEntity) {
			auto leftRender = m_LeftEntity->GetComponent<RenderComponent>();
			auto rightRender = m_RightEntity->GetComponent<RenderComponent>();
			
			if (leftRender && rightRender) {
				leftRender->SetShader(rightRender->GetShader());
			}
		}
		m_UseLeftShaderForBoth = false;
		m_UseRightShaderForBoth = true;
	}

	void RestoreOriginalShaders() {
		if (m_LeftEntity && m_RightEntity) {
			auto leftRender = m_LeftEntity->GetComponent<RenderComponent>();
			auto rightRender = m_RightEntity->GetComponent<RenderComponent>();
			
			if (leftRender) leftRender->SetShader(std::make_shared<Shader>(m_LeftShader));
			if (rightRender) rightRender->SetShader(std::make_shared<Shader>(m_RightShader));
		}
		m_UseLeftShaderForBoth = false;
		m_UseRightShaderForBoth = false;
	}

	void UpdateDynamicLight(float deltaTime) {
		float currentTime = static_cast<float>(glfwGetTime());
		currentLightPos = glm::vec3(
			initialLightLoc.x + sin(currentTime * 0.8f) * 3.0f,
			initialLightLoc.y + cos(currentTime * 0.6f) * 2.0f,
			initialLightLoc.z
		);
	}

private:
	std::string m_LeftShader;
	std::string m_RightShader;
	bool m_NeedsLighting;
};

// ============================ 便利宏定义 =============================

// 简单单对象场景宏
#define SIMPLE_DRAW_FUNCTION(FuncName, GeometryType, ShaderPath) \
void FuncName(GLFWwindow* window) { \
	SingleRotatingObjectScene<GeometryType> scene(ShaderPath); \
	scene.InitializeWithWindow(window); \
	scene.Initialize(); \
	\
	Renderer renderer; \
	RunRenderLoop(window, \
		[]() {}, \
		[&](float currentTime, float deltaTime) { \
			scene.Update(deltaTime); \
		}, \
		[&](float currentTime, float deltaTime) { \
			scene.Render(renderer); \
		} \
	); \
	scene.Cleanup(); \
}

// 带纹理的单对象场景宏
#define TEXTURED_DRAW_FUNCTION(FuncName, GeometryType, ShaderPath, TexturePath) \
void FuncName(GLFWwindow* window) { \
	SingleRotatingObjectScene<GeometryType> scene(ShaderPath, TexturePath); \
	scene.InitializeWithWindow(window); \
	scene.Initialize(); \
	\
	Renderer renderer; \
	RunRenderLoop(window, \
		[]() {}, \
		[&](float currentTime, float deltaTime) { \
			scene.Update(deltaTime); \
		}, \
		[&](float currentTime, float deltaTime) { \
			scene.Render(renderer); \
		} \
	); \
	scene.Cleanup(); \
}

// 双对象对比场景宏
#define DUAL_COMPARISON_FUNCTION(FuncName, LeftGeom, RightGeom, LeftShader, RightShader) \
void FuncName(GLFWwindow* window) { \
	DualObjectScene<LeftGeom, RightGeom> scene(LeftShader, RightShader, true); \
	scene.InitializeWithWindow(window); \
	scene.Initialize(); \
	\
	Renderer renderer; \
	glfwSetWindowTitle(window, #FuncName " | [G]左侧着色器 | [P]右侧着色器 | [C]对比模式"); \
	\
	RunRenderLoop(window, \
		[]() {}, \
		[&](float currentTime, float deltaTime) { \
			scene.Update(deltaTime); \
		}, \
		[&](float currentTime, float deltaTime) { \
			scene.Render(renderer); \
		} \
	); \
	scene.Cleanup(); \
}

// ============================ 使用示例宏创建常用函数 =============================

// 这些可以直接在 DrawDemo.cpp 中使用：
/*
SIMPLE_DRAW_FUNCTION(DrawSimpleCube, Cube, "res/shaders/Cube.shader")
SIMPLE_DRAW_FUNCTION(DrawSimpleSphere, Sphere, "res/shaders/Cube.shader")
SIMPLE_DRAW_FUNCTION(DrawSimpleTorus, Torus, "res/shaders/Cube.shader")

TEXTURED_DRAW_FUNCTION(DrawTexturedPyramid, Pyramid, "res/shaders/3DShaderWithTexture.shader", "res/textures/brick1.jpg")

DUAL_COMPARISON_FUNCTION(DrawShadowMapping, Sphere, Torus, "res/shaders/Gouraud.shader", "res/shaders/Blinn-Phong.shader")
*/