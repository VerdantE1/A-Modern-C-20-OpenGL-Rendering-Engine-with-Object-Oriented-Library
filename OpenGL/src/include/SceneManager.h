#pragma once
#include <memory>
#include <Scene.h>


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
    void Update(float deltaTime) {
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

