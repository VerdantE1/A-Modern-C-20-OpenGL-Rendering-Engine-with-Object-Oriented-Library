#pragma once
#include <memory>
#include <functional>
#include "Globals.h"
#include "Scene.h" 
#include "SceneManager.h"

class Engine {
public:
    using KeyboardHandler = std::function<void(int key, int action)>;

    WindowConfig windowConfig;
    SceneManager sceneManager;

    // 添加窗口状态管理
    int GetWindowWidth() const { return m_windowWidth; }
    int GetWindowHeight() const { return m_windowHeight; }

    static Engine* GetInstance() { return s_instance; }

    void Run(GLFWwindow* window) {

        s_instance = this;
        InitializeWindowState(window);

        auto scene = sceneManager.GetActiveScene();
        if (!scene)
        {
            LOG_ERROR("No active scene set in SceneManager. Exiting Run loop.");
            return;
        }

        //主循环
        while (!glfwWindowShouldClose(window)) {
            LOG_SUCCESS("New frame start.");


            LOG_LEVEL_INFO(1, "Engine: Processing UpdateTime and Input ");
            UpdateTime();
            UpdateWindowState(window);
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
        s_instance = nullptr; 
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
private:
    int m_windowWidth = 0;
    int m_windowHeight = 0;
    static inline Engine* s_instance = nullptr;

    void InitializeWindowState(GLFWwindow* window) {
        LOG_INFO("Engine: Initializing window state...");
        UpdateWindowState(window);
        LOG_INFO("\tWindow state initialized: {}x{}", m_windowWidth, m_windowHeight);
    }
    void UpdateWindowState(GLFWwindow* window) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        // 只在尺寸变化时更新
        if (width != m_windowWidth || height != m_windowHeight) {
            m_windowWidth = width;
            m_windowHeight = height;

            // 同步更新全局变量（兼容老代码）
            g_WindowWidth = width;
            g_WindowHeight = height;

            LOG_DEBUG("Engine: Window size updated to {}x{}", width, height);
        }
    }
};



