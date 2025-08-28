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