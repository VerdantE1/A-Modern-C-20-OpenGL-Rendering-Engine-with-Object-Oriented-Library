#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include "Entity.h"
#include "Camera.h"
#include "Renderer.h"

class Scene {
public:
    virtual ~Scene() = default;
    


    // 场景生命周期
    virtual void Initialize() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(const Renderer& renderer) = 0;
    virtual void Cleanup() = 0;
    
    // 实体管理
    Entity* CreateEntity(const std::string& name = "");
    void DestroyEntity(Entity* entity);
    
    // 摄像机管理
    void SetCamera(std::unique_ptr<Camera> camera);
    Camera& GetCamera() { return *m_Camera; }

    virtual Renderer& GetRenderer() = 0;
protected:
    std::vector<std::unique_ptr<Entity>> m_Entities; 
    std::unique_ptr<Camera> m_Camera;
	std::unordered_map<std::string, Entity*> m_NamedEntities;  // 通过名称快速查找实体
};

// 创建一个实体,如果提供了名称则注册,未提供名称则创建匿名实体;
inline Entity* Scene::CreateEntity(const std::string& name) {
    auto entity = std::make_unique<Entity>(name);
    Entity* entityPtr = entity.get();
    m_Entities.push_back(std::move(entity));
    if (!name.empty()) {
        m_NamedEntities[name] = entityPtr;
    }
    return entityPtr;
}

// 销毁实体,从场景中移除并释放资源;
inline void Scene::DestroyEntity(Entity* entity)
{
    auto it = std::remove_if(m_Entities.begin(), m_Entities.end(),
        [entity](const std::unique_ptr<Entity>& e) { return e.get() == entity; }
    );
    if (it != m_Entities.end())
    {
        if (!entity->GetName().empty()) {
            m_NamedEntities.erase(entity->GetName());
        }
		m_Entities.erase(it, m_Entities.end());
    }
}

inline void Scene::SetCamera(std::unique_ptr<Camera> camera) {
    m_Camera = std::move(camera);
}