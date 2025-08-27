#pragma once

class Entity; // 前向声明

class Component {
public:
    Component() = default;
    virtual ~Component() = default;
    
    // 组件生命周期方法
    virtual void Initialize() {}
    virtual void Update(float deltaTime) {}
    virtual void Destroy() {}
    
    // 获取拥有该组件的实体
    Entity* GetOwner() const { return m_Owner; }
    
protected:
    Entity* m_Owner = nullptr;
    
    friend class Entity; // 允许 Entity 设置 m_Owner
};