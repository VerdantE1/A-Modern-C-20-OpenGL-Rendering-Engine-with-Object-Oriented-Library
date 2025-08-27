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

protected:
    std::vector<std::unique_ptr<Entity>> m_Entities;
    std::unique_ptr<Camera> m_Camera;
    std::unordered_map<std::string, Entity*> m_NamedEntities;
};