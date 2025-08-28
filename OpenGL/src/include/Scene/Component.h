#pragma once

class Entity; // 前向声明
class Shader; // 前向声明

/*
* Component 是所有组件的基类. 
* 组件用于为实体(Entity)添加特定的功能或数据.
* 组件可以是渲染组件、物理组件、动画组件等.
* 组件可以初始化、更新和销毁.
*/

class Component {
public:
    Component() = default;
    virtual ~Component() = default;
    
    // 组件生命周期方法
    virtual void Initialize() {}
    
    // Update：只处理 CPU 中的数据，不涉及 GPU 状态,只把数据准备好
    virtual void Update(float deltaTime) {}
    
    // ApplyToShader：专门用于渲染时传递 uniform 数据到 Shader
    virtual void ApplyToShader(Shader& shader) {}
    
    virtual void Destroy() {}
    
    // 获取拥有该组件的实体
    Entity* GetOwner() const { return m_Owner; }
    
protected:
    Entity* m_Owner = nullptr;
    
    friend class Entity; // 允许 Entity 设置 m_Owner
};